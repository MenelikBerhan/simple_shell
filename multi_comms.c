#include "main.h"

/**
 * free_all_t - free all token variables
 * @l: line string
 * @c: var 1
 * @c2: var 2
 * @c3: var 3
 */
void free_all_t(char *l, char **c, char **c2, char **c3)
{
	free(l);
	free(c);
	free(c2);
	free(c3);
}

/**
 * neg_exit - handles exit with negative exit codes
 * @temp: current exit command
 * @sh: shell name
 * @status: status buffer
 *
 * Return: 1 if is negative, 0 otherwise
 */
int neg_exit(char *temp, char *sh, int *status)
{
	char *t = temp + strcspn(temp, " "), *t2;
	char *nums = "0123456789";
	int e_c;

	if (strspn(t, " "))
	{
		e_c = atoi(t + 1);
		t2 = t + strspn(t + 1, nums) + 1;
		if (*t2 != '\0' || e_c < 0)
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", sh, (t + 1));
			*status = 2;
			free(temp);
			return (1);
		}
	}
	return (0);
}

/**
 * multi_comms - splits multiple comm and runs them
 * @f: read from file
 * @sh: shell name
 * @line: line input
 * @alias: alias list
 * @paths: paths array
 * @o_env_adrs: pointer to a pointer to the original environ.
 * @o_env_elms: pointer to an array of original environ elements address.
 */
void multi_comms(int f, char *sh, char *line, Alias **alias, char **paths,
				 char **o_env_adrs, char **o_env_elms)
{
	char *temp, **comm = NULL, **comm2 = NULL, **comm3 = NULL;
	int i, j, k, is_exit, is_neg;
	static int status = 100000;

	handle_comment(line);
	comm = _strtok(line, ";\n");
	for (i = 0; comm && comm[i] != NULL; i++)
	{
		comm2 = _strtok(comm[i], "&&");
		for (j = 0; comm2[j] != NULL; j++)
		{
			comm3 = _strtok(comm2[j], "||");
			for (k = 0; comm3[k] != NULL; k++)
			{
				status = status == 100000 ? 0 : status;
				temp = handle_expansion(strdup(comm3[k]), status);
				is_exit = strspn(comm3[k], "exit");
				if (is_exit == 4 || is_exit == 5)
				{
					is_neg = neg_exit(temp, sh, &status);
					if (is_neg)
						continue;
					free_all_t(line, comm, comm2, comm3);
				}
				status = run_comm(status, sh, temp, alias, paths, o_env_adrs,
								  o_env_elms);
				free(temp);
				if (!status)
					break;
			}
			free(comm3);
			if (status)
				break;
		}
		free(comm2);
	}
	free(comm);
	status = status == 100000 ? 0 : status;
	if (!isatty(STDIN_FILENO) && !f)
		exit_shell(1, status, line, NULL, paths, alias, o_env_adrs, o_env_elms);
}
