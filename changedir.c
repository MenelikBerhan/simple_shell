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
		fprintf(stderr, "%s: cd: %s: No such file or directory\n", sh, path);
	return (-1);
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
	static char oldpwd[PATH_MAX];
	char currpwd[PATH_MAX], fullpwd[PATH_MAX], *home;

	if (!(getcwd(currpwd, sizeof(currpwd))))
		return (cd_errors(sh, NULL));
	if (t[1] == NULL)
	{
		home = _getenv("HOME");
		if (!home)
			return (1);
		strncpy(fullpwd, home, sizeof(fullpwd) - 1);
		fullpwd[sizeof(fullpwd) - 1] = '\0';
	}
	else if (t[1][0] == '/')
	{
		strncpy(fullpwd, t[1], sizeof(fullpwd) - 1);
		fullpwd[sizeof(fullpwd) - 1] = '\0';
	}
	else if (strcmp(t[1], "-") == 0)
	{
		strncpy(fullpwd, oldpwd, sizeof(fullpwd) - 1);
		fullpwd[sizeof(fullpwd) - 1] = '\0';
	}
	else
		snprintf(fullpwd, sizeof(fullpwd) + 2, "%s/%s", currpwd, t[1]);
	if (chdir(fullpwd) == 0)
	{
		strncpy(oldpwd, currpwd, sizeof(oldpwd) - 1);
		oldpwd[sizeof(oldpwd) - 1] = '\0';
		if (_setenv("PWD", fullpwd, 1, o_env_elms))
			return (cd_errors("setenv() error", NULL));
	}
	else
		return (cd_errors(sh, t[1]));
	return (0);
}
