#include "main.h"

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
	char *temp, **comm = NULL, **comm2 = NULL, **comm3 = NULL, status_code[20];
	int i, j, k, status, is_exit;

	handle_comment(line);
	comm = _strtok(line, ";\n");
	for (i = 0; comm[i] != NULL; i++)
	{
		comm2 = _strtok(comm[i], "&&");
		for (j = 0; comm2[j] != NULL; j++)
		{
			comm3 = _strtok(comm2[j], "||");
			for (k = 0; comm3[k] != NULL; k++)
			{
				is_exit = strspn(comm3[k], " exit");
				if (is_exit == 4 || is_exit == 5)
				{
					temp = strdup(comm3[k]);
					free(line);
					free(comm3);
					free(comm2);
					free(comm);
					run_comm(sh, temp, alias, paths, o_env_adrs, o_env_elms);
				}
				status = run_comm(sh, comm3[k], alias, paths, o_env_adrs, o_env_elms);
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
	{
		snprintf(status_code, sizeof(status_code), "%d", status);
		exit_shell(1, status_code, line, NULL, paths, alias, o_env_adrs,
				   o_env_elms);
	}
}
