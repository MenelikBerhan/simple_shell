#include "main.h"

/**
 * handle_inbuilts - handle inbuilt commands e.g cd, exit
 * @sh: shell name
 * @l: line string
 * @p: system paths
 * @t: input tokens
 * @a: current alias list
 *
 * Return: 1 if not inbuild command, 0 otherwise
 */
int handle_inbuilts(char *sh, char *l, char **p, char **t, Alias **a)
{
	int status = 0;

	if (!strcmp(t[0], "exit"))
	{
		if (t[1])
			exit_shell(strdup(t[1]), l, t, p, a);
		else
			exit_shell(NULL, l, t, p, a);
	}
	if (!strcmp(t[0], "cd"))
	{
		status = changedir(sh, t);
		if (!status)
			free(t);
		return (status);
	}
	if (!strcmp(t[0], "alias"))
	{
		status = _alias(sh, t, a);
		if (!status)
			free(t);
		return (status);
	}
	return (-1);
}
