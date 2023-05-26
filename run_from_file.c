#include "main.h"

/**
 * run_frm_file - runs simple shell when read from file.
 * @argv: argument vector
 *
 * Return: Always 0 (Success)
 */
int run_frm_file(char *argv[])
{
	char *line, **paths;
	ssize_t nread;
	FILE *fp;
	Alias *l_alias = NULL;
	char **o_env_adrs = NULL, **o_env_elms = NULL;
	struct stat st;

	if (stat(argv[1], &st) != 0)
	{
		fprintf(stderr, "%s: %d: Can't open %s\n", argv[0], 0, argv[1]);
		exit(127);
	}
	else
		fp = fopen(argv[1], "r");
	o_env_adrs = environ;
	o_env_elms = malloc(sizeof(char *) * (_get_null_index() + 1));
	o_env_elms = memcpy(o_env_elms, environ,
						(sizeof(char *) * (_get_null_index() + 1)));
	paths = get_path(environ);
	while ((nread = _get_line(&line, fp)) != -1)
	{
		if ((nread == 1 && *line == 10) || nread == 0)
		{
			free(line);
			continue;
		}
		if (line[nread - 1] == 10)
			line[nread - 1] = 0;
		trim_in(line);
		multi_comms(1, argv[0], line, &l_alias, paths, o_env_adrs,
					o_env_elms);
		free(line);
	}
	fclose(fp);
	free(line);
	free(*paths);
	free(paths);
	free_alias(l_alias);
	free_environ(-1, o_env_adrs, o_env_elms);
	return (0);
}
