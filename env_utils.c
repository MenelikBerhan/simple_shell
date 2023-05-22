#include "main.h"

/**
 * free_environ - if index = -1 frees environ and its elements if they are
 * malloc'ed in heap, otherwise frees only the element at index if malloc'ed.
 * @index: index of environment variable to free, or -1 to free all.
 * @o_env_adrs: pointer to a pointer to the original environ.
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: 0 if successful or -1 if failure.
*/
int free_environ(int index, char **o_env_adrs, char **o_env_elms)
{
	int i, j;

	if (!o_env_adrs && !o_env_elms)
		return (0);

	if (index != -1)
	{
		for (j = 0; o_env_elms && o_env_elms[j]; j++)
			if (o_env_elms[j] == environ[index])
				break;
		if (!o_env_elms[j])
			free(environ[index]);
	}
	else
	{
		for (i = 0; environ && environ[i]; i++)
		{
			for (j = 0; o_env_elms && o_env_elms[j]; j++)
				if (o_env_elms[j] == environ[i])
					break;
			if (!o_env_elms[j])
				free(environ[i]);
		}
		if (o_env_adrs != environ)
			free(environ);
		free(o_env_elms);
	}

	return (0);
}


/**
 * _getindex - finds the index of environment variable 'name' in
 * the environment list pointed by envptr.
 * @name: name of environment variable.
 * @envptr: pointer to an environment.
 *
 * Return: index of name if found in environment pointed by envptr, or else -1.
*/
int _getindex(const char *name, char **envptr)
{
	int i, len, index = -1;

	len = strlen(name);
	for (i = 0; envptr && envptr[i]; i++)
	{
		if (!strncmp(name, envptr[i], len) && envptr[i][len] == '=')
		{
			index = i;
			break;
		}
	}
	return (index);
}


/**
 * _get_null_index - finds the last index of environ (element NULL).
 *
 * Return: index of NULL in environ if environ exists, or -1.
*/
int _get_null_index(void)
{
	int i = -1;

	for (i = 0; environ && environ[i]; i++)
		continue;
	return (i);
}


/**
 * _getenv - finds the value of an environment variable named 'name'.
 * @name: name of environment variable
 *
 * Return: a pointer to the value of the environment variable, or NULL if not
 * found.
 * Note: modifying the retuned string changes the environment of the process.
*/
char *_getenv(const char *name)
{
	int i, len;

	if (!name || !(*name))
		return (NULL);
	len = strlen(name);
	for (i = 0; i < len; i++)
	{
		if (name[i] == '=')
			return (NULL);
	}
	for (i = 0; environ && environ[i]; i++)
	{
		if (!strncmp(name, environ[i], len) && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}
