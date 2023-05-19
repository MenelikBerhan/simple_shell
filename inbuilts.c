#include "main.h"

/**
 * handle_inbuilts - handle inbuilt commands e.g cd, exit
 * @sh: shell name
 * @l: line string
 * @p: system paths
 * @t: input tokens
 * @a: current alias list
 *
 * Return: 0 if not inbuild command, 1 otherwise
 */
int handle_inbuilts(char *sh, char *l, char **p, char **t, Alias **a)
{
	if (!strcmp(t[0], "exit"))
	{
		if (t[1])
			exit_shell(strdup(t[1]), l, t, p, a);
		else
			exit_shell(NULL, l, t, p, a);
	}
	if (!strcmp(t[0], "cd"))
	{
		changedir(sh, t);
		free(t);
		prompt();
		return (1);
	}
	if (!strcmp(t[0], "alias"))
	{
		_alias(sh, t, a);
		free(t);
		prompt();
		return (1);
	}
	return (0);
}
