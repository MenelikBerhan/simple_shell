#include "main.h"

char **o_env_adrs = NULL;
char **o_env_elms = NULL;

/**
 * free_environ - if index = -1 frees environ and its elements if they are
 * malloc'ed in heap, otherwise frees only the element at index if malloc'ed.
 * @index: index of environment variable to free, or -1 to free all.
 *
 * Return: 0 if successful or -1 if failure.
*/
int free_environ(int index)
{
	int i, j;

	if (!o_env_adrs || !o_env_elms)
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
 * _getindex - finds the last index of environ (element NULL).
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
 * _getindex - finds the index of environment variable 'name' in
 * the environment list pointed by envptr.
 * @name: name of environment variable.
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


/**
 * env - prints the current environment.
 *
*/
void env(void)
{
	int i = 0;

	while (environ && environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * init_setenv - helper to initialize _setenv fuction.
 * @name: name of environment variable.
 * @old_exist: pointer to integer showing if initial environ is copied
 *
 * Return: 0 is succesful, otherwise -1.
*/
int init_setenv(const char *name, int *old_exist)
{
	int i, len_name, null_index;

	if (!name || !(*name))
		return (-1);
	len_name = strlen(name);
	for (i = 0; i < len_name; i++)
	{
		if (name[i] == '=')
			return (-1);
	}
	null_index = (_get_null_index());
	if ((*old_exist) == -1)
	{
		o_env_adrs = environ;
		o_env_elms = malloc(sizeof(char *) * (null_index + 1));
		o_env_elms = memcpy(o_env_elms, environ,
							(sizeof(char *) * (null_index + 1)));
		*old_exist = 1;
	}
	return (0);
}


/**
 * _setenv - if an environment variable `name` does not exist adds a variable
 * named `name` with value of `value`. If `name` exists and `overwrite` is
 * non-zero changes value of name to `value`.
 * @name: name of environment variable
 * @value: value of environment variable
 * @overwrite: overwrite flag incase 'name' already exists.
 *
 * Return: 0 if successful, or -1 if name is null, points to a string of
 * length zero or contains '=', or if there is insufficient memory to add
 * a new variable.
*/
int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_var, **new_environ;
	int len_name, len_value, null_index, index;
	static int environ_alloced = -1, old_exist = -1;

	if (init_setenv(name, &old_exist) == -1)
		return (-1);
	len_name = strlen(name);
	index = _getindex(name, environ);
	null_index = (_get_null_index());
	len_value = strlen(value);
	if (index != -1 && !overwrite)
		return (0);
	new_var = malloc(sizeof(char) * (len_name + len_value + 2));
	strncpy(new_var, name, len_name);
	new_var[len_name] = '=';
	strcpy((new_var + len_name + 1), value);
	if (index != -1)
	{
		free_environ(index);
		environ[index] = new_var;
	}
	else
	{
		if (environ_alloced == -1)
		{
			new_environ = malloc((null_index + 2) * sizeof(char *));
			memcpy(new_environ, environ, (sizeof(char *) * null_index));
			new_environ[null_index] = new_var;
			new_environ[null_index + 1] = NULL;
			environ = new_environ;
			environ_alloced = 1;
		}
		else
		{
			environ = realloc(environ, ((null_index + 2) * sizeof(char *)));
			environ[null_index] = new_var;
			environ[null_index + 1] = NULL;
		}
	}
	return (0);
}

/**
 * _unsetenv - deletes variable named `name` from the environment
 * @name: name of environment variable.
 *
 * Return: 0 if successful, or -1 if name is null, points to a string of
 * length zero or contains '='.
*/
int _unsetenv(const char *name)
{
	int i, len_name, index, null_index;

	if (!name || !(*name))
		return (-1);
	len_name = strlen(name);
	for (i = 0; i < len_name; i++)
	{
		if (name[i] == '=')
			return (-1);
	}
	index = _getindex(name, environ);
	if (index == -1)
		return (0);

	free_environ(index);
	null_index = _get_null_index();
	for (i = index; i < null_index; i++)
		environ[index] = environ[index + 1];
	return (0);
}
