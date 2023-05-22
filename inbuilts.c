#include "main.h"

/**
 * handle_inbuilts - handle inbuilt commands e.g cd, exit
 * @sh: shell name
 * @l: line string
 * @p: system paths
 * @t: input tokens
 * @a: current alias list
 * @o_env_adrs: pointer to a pointer to the original environ.
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: 1 if not inbuild command, 0 otherwise
 */
int handle_inbuilts(char *sh, char *l, char **p, char **t, Alias **a,
								char **o_env_adrs, char **o_env_elms)
{
	int status = 0;

	if (!strcmp(t[0], "exit"))
	{
		if (t[1])
			exit_shell(strdup(t[1]), l, t, p, a, o_env_adrs, o_env_elms);
		else
			exit_shell(NULL, l, t, p, a, o_env_adrs, o_env_elms);
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
	if (!strcmp(t[0], "env") && !t[1])
	{
		_env();
		free(t);
		return (0);
	}
	if (!(strcmp(t[0], "setenv")) || !(strcmp(t[0], "unsetenv")))
	{
		status = set_unset_env(t, o_env_elms);
		free(t);
		return (status);
	}
	return (-2);
}
