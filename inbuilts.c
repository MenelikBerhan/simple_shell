#include "main.h"

/**
 * free_t - free input tokens
 * @u_a: is alias used
 * @t: input tokens
 */
void free_t(int u_a, char **t)
{
	if (!u_a)
		free(*t);
	free(t);
}

/**
 * handle_inbuilts - handle inbuilt commands e.g cd, exit
 * @u_a: is command an alias
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
int handle_inbuilts(int u_a, char *sh, char *l, char **p, char **t, Alias **a,
					char **o_env_adrs, char **o_env_elms)
{
	int status = 0;

	if (!strcmp(t[0], "exit"))
		exit_shell(u_a, 0, l, t, p, a, o_env_adrs, o_env_elms);
	if (!strcmp(t[0], "cd"))
	{
		status = changedir(sh, t, o_env_elms);
		if (!status)
			free_t(u_a, t);
		return (status);
	}
	if (!strcmp(t[0], "alias"))
	{
		status = _alias(sh, t, a);
		if (!status)
			free_t(u_a, t);
		return (status);
	}
	if (!strcmp(t[0], "env") && !t[1])
	{
		_env();
		status = 0;
		if (!status)
			free_t(u_a, t);
		return (0);
	}
	if (!(strcmp(t[0], "setenv")) || !(strcmp(t[0], "unsetenv")))
	{
		status = set_unset_env(t, o_env_elms);
		if (!status)
			free_t(u_a, t);
		return (status);
	}
	return (-2);
}
