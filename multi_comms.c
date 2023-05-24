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
	int i, j, k, is_exit;
	static int status = 1;

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
				temp = handle_expansion(strdup(comm3[k]), status);
				is_exit = strspn(comm3[k], "exit");
				if (is_exit == 4 || is_exit == 5)
					free_all_t(line, comm, comm2, comm3);
				status = run_comm(sh, temp, alias, paths, o_env_adrs,
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
	if (!isatty(STDIN_FILENO) && !f)
		exit_shell(1, status, line, NULL, paths, alias, o_env_adrs, o_env_elms);
}
