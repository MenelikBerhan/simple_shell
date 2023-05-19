#include "main.h"

/**
 * cd_errors - prints the error messages for cd
 * @sh: shell name
 * @path: path that generated error
 */
void cd_errors(char *sh, char *path)
{
	if (path && !strcmp(path, "-"))
		fprintf(stderr, "%s: cd: OLDPWD not set\n", sh);
	else if (strspn(path, "-/") == 2)
	{
		fprintf(stderr, "%s: cd: -/: invalid option\n", sh);
		fprintf(stderr, "cd: usage: cd [-L|-P] [dir]\n");
	}
	else
		fprintf(stderr, "%s: cd: %s: No such file or directory\n", sh, path);
}

/**
 * changedir - change directories
 * @sh: shell name
 * @t: input tokens
 */
void changedir(char *sh, char **t)
{
	static char oldpwd[PATH_MAX];
	char currpwd[PATH_MAX], fullpwd[PATH_MAX], *home;

	if (!(getcwd(currpwd, sizeof(currpwd))))
	{
		perror(sh);
		return;
	}
	if (t[1] == NULL)
	{
		home = getenv("HOME");
		if (!home)
			return;
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
		snprintf(fullpwd, sizeof(fullpwd), "%s/%s", currpwd, t[1]);
	if (chdir(fullpwd) == 0)
	{
		strncpy(oldpwd, currpwd, sizeof(oldpwd) - 1);
		oldpwd[sizeof(oldpwd) - 1] = '\0';
		if (setenv("PWD", fullpwd, 1))
		{
			perror("setenv() error");
			return;
		}
	}
	else
		cd_errors(sh, t[1]);
}
