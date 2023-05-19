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
	size_t len;
	char *line, **tokens, *full_path, **paths;
	ssize_t nread;
	FILE *fp = stdin;
	Alias *l_alias;
	(void)argc;

	signal(SIGINT, handleSigInt);

	line = malloc(sizeof(char) * 2);
	len = 2;
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
		tokens = _strtok(line, " ");
		check_alias(l_alias, &tokens);
		if (handle_inbuilts(argv[0], line, paths, tokens, &l_alias))
			continue;
		full_path = add_path(tokens[0], paths);
		if (full_path)
			child_proc(argv[0], full_path, tokens);
		else
			perror(argv[0]);
		free(tokens);
		prompt();
	}
	free(line);
	free(paths);
	free_alias(l_alias);
	return (0);
}
