#include "main.h"

/**
 * get_path - finds the PATH variable in environ
 * @environ: apointer to a NULL terminated array of environment variables.
 *
 * Return: a pointer to an array of PATH variable values
*/
char **get_path(char **env)
{
	char *path, **paths;
	int i/* , j */;

	for (i = 0; env && env[i]; i++)
	{
		if (strspn(env[i], "PATH=") == 5)
		{
			path = env[i];
			break;
		}
	}
	if (!path)
		return (NULL);
	path += 5; /* pass "PATH=" */
	paths = _strtok(path, ":");
	if (!paths)
		return (NULL);

	return (paths); /* free *paths and paths */
}

/**
 * add_path - searches a file_name in PATH values and if found prefix path to it.
 * @file_name: name of file to be found
 * @paths: a pointer to an array of PATH variable values.
 *
 * Return: a full path file name if file is found, or else NULL.
*/
char *add_path(char *file_name, char **paths)
{
	struct stat st;
	char *full_path;
	int i, new_size;

	if (stat(file_name, &st) == 0)
			return (strdup(file_name)); /* free full_path when done in calling function */
	if (*file_name == '/')
		file_name++;
	for (i = 0; paths && paths[i]; i++)
	{
		full_path = strdup(paths[i]);
		new_size = (strlen(full_path) + 1) + 1 + strlen(file_name);
		full_path = realloc(full_path, new_size);
		strcat(full_path, "/");
		strcat(full_path, file_name);

		if (stat(full_path, &st) == 0)
			return (full_path); /* free full_path when done in calling function */
		free(full_path);
	}
	if (i == 0)
		free(full_path);
	return (NULL);
}
