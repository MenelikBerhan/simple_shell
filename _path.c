#include "main.h"

/**
 * get_path - finds the PATH variable in environ
 * @env: a pointer to a NULL terminated array of environment variables.
 *
 * Return: a pointer to an array of PATH variable values
 */
char **get_path(char **env)
{
	char *path = NULL, **paths;
	int i;

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
	path += 5;
	paths = _strtok(path, ":");
	if (!paths)
		return (NULL);
	return (paths);
}

/**
 * add_path - prefixes the right path to a command if any.
 * @file_name: name of file to be found
 * @paths: a pointer to an array of PATH variable values.
 *
 * Return: a full path file name if file is found, or else NULL.
 */
char *add_path(char *file_name, char **paths)
{
	struct stat st;
	char *full_path = NULL;
	int i, new_size;

	if (stat(file_name, &st) == 0)
		return (strdup(file_name));
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
			return (full_path);
		free(full_path);
	}
	return (NULL);
}
