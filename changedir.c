#include "main.h"

/**
 * cd_errors - prints the error messages for cd
 * @sh: shell name
 * @path: path that generated error
 *
 * Return: always -1 (success)
 */
int cd_errors(char *sh, char *path)
{
	if (!path)
		perror(sh);
	if (!strcmp(path, "-"))
		fprintf(stderr, "%s: cd: OLDPWD not set\n", sh);
	else if (strspn(path, "-/") == 2)
	{
		fprintf(stderr, "%s: cd: -/: invalid option\n", sh);
		fprintf(stderr, "cd: usage: cd [-L|-P] [dir]\n");
	}
	else
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", sh, path);
	return (-1);
}

/**
 * set_envs - set the PWD and OLDPWD envs
 * @oldpwd: oldpwd content
 * @fullpwd: fullpwd content
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: 0 if successful and -1 otherwise
 */
int set_envs(char *oldpwd, char *fullpwd, char **o_env_elms)
{
	if (_setenv("OLDPWD", oldpwd, 1, o_env_elms))
		return (cd_errors("setenv() error", NULL));
	if (_setenv("PWD", fullpwd, 1, o_env_elms))
		return (cd_errors("setenv() error", NULL));
	return (0);
}

/**
 * changedir - change directories
 * @sh: shell name
 * @t: input tokens
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: process status
 */
int changedir(char *sh, char **t, char **o_env_elms)
{
	char currpwd[PATH_MAX], fullpwd[PATH_MAX], oldpwd[PATH_MAX] = "", *h, *o;

	if (!(getcwd(currpwd, sizeof(currpwd))))
		return (cd_errors(sh, NULL));
	o = _getenv("OLDPWD");
	if (o)
		strncpy(oldpwd, o, sizeof(oldpwd) - 1);
	if (t[1] == NULL)
	{
		h = _getenv("HOME");
		if (!h)
			return (1);
		strncpy(fullpwd, h, sizeof(fullpwd) - 1);
		fullpwd[sizeof(fullpwd) - 1] = '\0';
	}
	else if (t[1][0] == '/')
	{
		strncpy(fullpwd, t[1], sizeof(fullpwd) - 1);
		fullpwd[sizeof(fullpwd) - 1] = '\0';
	}
	else if (strcmp(t[1], "-") == 0)
	{
		if (!(*oldpwd))
			strncpy(fullpwd, currpwd, sizeof(fullpwd) - 1);
		else
			strncpy(fullpwd, oldpwd, sizeof(fullpwd) - 1);
		fullpwd[sizeof(fullpwd) - 1] = '\0';
		printf("%s\n", fullpwd);
	}
	else
		snprintf(fullpwd, sizeof(fullpwd) + 2, "%s/%s", currpwd, t[1]);
	if (chdir(fullpwd) == 0)
	{
		strncpy(oldpwd, currpwd, sizeof(oldpwd) - 1);
		oldpwd[sizeof(oldpwd) - 1] = '\0';
		return (set_envs(oldpwd, fullpwd, o_env_elms));
	}
	else
		return (cd_errors(sh, t[1]));
}
