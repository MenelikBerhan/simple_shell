#include "main.h"

/**
 * handle_inbuilts - handle inbuilt commands e.g cd, exit
 * @sh: shell name
 * @l: line string
 * @p: system paths
 * @t: input tokens
 *
 * Return: 0 if not inbuild command, 1 otherwise
 */
int handle_inbuilts(char *sh, char *l, char **p, char **t)
{
	if (!strcmp(t[0], "exit"))
		exit_shell(strdup(t[1]), l, t, p);
	if (!strcmp(t[0], "cd"))
	{
		changedir(sh, t);
		free(t);
		prompt();
		return (1);
	}
	return (0);
}
