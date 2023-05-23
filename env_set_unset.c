#include "main.h"

/**
 * _env - prints the current environment.
 *
*/
void _env(void)
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
 * set_unset_error - prints an error message.
 * @error: integer indicating error type.
 *
 * Return: always -1 successful or 1 for failure.
*/
int set_unset_error(int error)
{
	if (error == 0)
	{
		write(STDERR_FILENO, "error: name can't be a NULL pointer ", 36);
		write(STDERR_FILENO, "or zero length string\n", 22);
		return (-1);
	}
	if (error == 1)
	{
		write(STDERR_FILENO, "error: the first character of name ", 35);
		write(STDERR_FILENO, "should be a letter or '_'\n", 26);
		return (-1);
	}
	if (error == 2)
	{
		write(STDERR_FILENO, "error: name can't contain '='\n", 30);
		return (-1);
	}
	if (error == 3)
	{
		write(STDERR_FILENO, "error: proper usage: setenv VARIABLE VALUE\n", 43);
		return (-1);
	}
	if (error == 4)
	{
		write(STDERR_FILENO, "error: proper usage: unsetenv VARIABLE\n", 39);
		return (-1);
	}
	return (1);
}


/**
 * set_unset_env - a helper function that calls setenv or unsetenv.
 * @tokens: pointer to an array of command arguments.
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: 0 if successful, or -1 if the number of arguments in tokens is
 * incorrect ,if tokens[0] is null, points to a string of length zero or
 * contains '='.
*/
int set_unset_env(char **tokens, char **o_env_elms)
{
	int i, len_name;
	char *e = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

	if (!(tokens[1]) || !(*(tokens[1])))
		return (set_unset_error(0));
	if (strcspn(tokens[1], e))
		return (set_unset_error(1));
	len_name = strlen(tokens[1]);
	for (i = 0; i < len_name; i++)
	{
		if (tokens[1][i] == '=')
			return (set_unset_error(2));
	}
	if (!strcmp(tokens[0], "setenv"))
	{
		if (!tokens[2] || tokens[3])
			return (set_unset_error(3));
		return (_setenv(tokens[1], tokens[2], 1, o_env_elms));
	}
	if (!strcmp(tokens[0], "unsetenv"))
	{
		if (!tokens[1] || tokens[2])
			return (set_unset_error(4));
		return (_unsetenv(tokens[1], o_env_elms));
	}
	return (-1);
}

/**
 * _setenv - if an environment variable `name` does not exist adds a variable
 * named `name` with value of `value`. If `name` exists and `overwrite` is
 * non-zero changes value of name to `value`.
 * @name: name of environment variable
 * @value: value of environment variable
 * @overwrite: overwrite flag incase 'name' already exists.
 * @o_en_el: pointer to an array of original environ elements address.
 *
 * Return: 0 if successful, or -1 there is insufficient memory to add
 * a new variable.
*/
int _setenv(const char *name, const char *value, int overwrite, char **o_en_el)
{
	char *new_var, **new_environ;
	int len_name, len_value, null_index, index;
	static int environ_alloced = -1;

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
		free_environ(index, NULL, o_en_el);
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
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: 0 if successful, or -1 for failure.
*/
int _unsetenv(const char *name, char **o_env_elms)
{
	int i, index, null_index;

	index = _getindex(name, environ);
	if (index == -1)
		return (0);

	null_index = _get_null_index();
	free_environ(index, NULL, o_env_elms);
	for (i = index; i < null_index; i++)
		environ[i] = environ[i + 1];
	return (0);
}
