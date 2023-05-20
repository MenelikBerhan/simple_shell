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
	char **comm = NULL, **comm2 = NULL, **comm3 = NULL;
	int i, j, k, status;

	comm = _strtok(line, ";");
	for (i = 0; comm[i] != NULL; i++)
	{
		comm2 = _strtok(comm[i], "&&");
		for (j = 0; comm2[j] != NULL; j++)
		{
			comm3 = _strtok(comm2[j], "||");
			for (k = 0; comm3[k] != NULL; k++)
			{
				status = run_comm(sh, comm3[k], alias, paths);
				if (!status)
					break;
			}
			if (status)
				break;
		}
	}
}
