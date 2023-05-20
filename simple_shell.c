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
	(void)argc;

	signal(SIGINT, handleSigInt);

	line = malloc(sizeof(char) * 2);
	memset(line, 0, 2);
	prompt();
	paths = get_path(environ);
	while ((nread = _get_line(&line, fp)) != -1)
	{
		if (nread == 1 && *line == 10)
		{
			prompt();
			continue;
		}
		if (line[nread - 1] == 10)
			line[nread - 1] = 0;
		trim_in(line);
		multi_comms(argv[0], line, &l_alias, paths);
		prompt();
	}
	free(line);
	free(*paths);
	free(paths);
	free_alias(l_alias);
	return (0);
}
