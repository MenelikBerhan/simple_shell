#include "main.h"

/**
 * multi_comms - splits multiple comm and runs them
 * @sh: shell name
 * @line: line input
 * @alias: alias list
 * @paths: paths array
 */
void multi_comms(char *sh, char *line, Alias **alias, char **paths)
{
	char *temp, **comm = NULL, **comm2 = NULL, **comm3 = NULL;
	char status_code[20];
	int i, j, k, status, is_exit;

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
					run_comm(sh, temp, alias, paths);
				}
				status = run_comm(sh, comm3[k], alias, paths);
				if (!status)
					break;
			}
			if (status)
				break;
			free(comm3);
		}
		free(comm2);
	}
	free(comm);
	if (!isatty(STDIN_FILENO))
	{
		snprintf(status_code, sizeof(status_code), "%d", status);
		exit_shell(1, status_code, line, NULL, paths, alias);
	}
}
