#include "main.h"

/**
 * multi_comms - splits multiple comm and runs them
 * @sh: shell name
 * @line: line input
 * @alias: alias list
 * @paths: paths array
 * @o_env_adrs: pointer to a pointer to the original environ.
 * @o_env_elms: pointer to an array of original environ elements address.
 */
void multi_comms(char *sh, char *line, Alias **alias, char **paths,
								char **o_env_adrs, char **o_env_elms)
{
	char **comm = NULL, **comm2 = NULL, **comm3 = NULL;
	char status_code[20];
	int i, j, k, status;

	comm = _strtok(line, ";\n");
	for (i = 0; comm[i] != NULL; i++)
	{
		comm2 = _strtok(comm[i], "&&");
		for (j = 0; comm2[j] != NULL; j++)
		{
			comm3 = _strtok(comm2[j], "||");
			for (k = 0; comm3[k] != NULL; k++)
			{
				status = run_comm(sh, comm3[k], alias, paths, **o_env_adrs,
																**o_env_elms);
				if (!status)
					break;
			}
			if (status)
				break;
		}
	}
	if (!isatty(STDIN_FILENO))
	{
		snprintf(status_code, sizeof(status_code), "%d", status);
		exit_shell(status_code, line, NULL, paths, alias, o_env_adrs,
															o_env_elms);
	}
}
