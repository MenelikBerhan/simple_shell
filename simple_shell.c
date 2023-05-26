#include "main.h"

/**
 * main - simple shell.
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	char *line, **paths;
	ssize_t nread;
	FILE *fp = stdin;
	Alias *l_alias = NULL;
	char **o_env_adrs = NULL, **o_env_elms = NULL;

	if (argc == 2)
		return (run_frm_file(argv));
	o_env_adrs = environ;
	o_env_elms = malloc(sizeof(char *) * (_get_null_index() + 1));
	o_env_elms = memcpy(o_env_elms, environ,
						(sizeof(char *) * (_get_null_index() + 1)));
	signal(SIGINT, handleSigInt);
	prompt();
	while ((nread = _get_line(&line, fp)) != -1)
	{
		if ((nread == 1 && *line == 10) || nread == 0)
		{
			free(line);
			prompt();
			continue;
		}
		if (line[nread - 1] == 10)
			line[nread - 1] = 0;
		trim_in(line);
		paths = get_path(environ);
		multi_comms(0, argv[0], line, &l_alias, paths, o_env_adrs,
					o_env_elms);
		free(line);
		if (paths)
		{
			free(*paths);
			free(paths);
		}
		prompt();
	}
	free(line);
	free_alias(l_alias);
	free_environ(-1, o_env_adrs, o_env_elms);
	return (0);
}
