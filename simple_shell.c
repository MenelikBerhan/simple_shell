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
	(void)argc;

	signal(SIGINT, handleSigInt);

	line = malloc(sizeof(char) * 2);
	len = 2;
	memset(line, 0, 2);
	prompt();
	paths = get_path(environ);
	while ((nread = getline(&line, &len, fp)) != -1)
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
		if (!strcmp(tokens[0], "exit"))
			exit_shell(tokens[1], line, tokens, paths);
		full_path = add_path(tokens[0], paths);
		if (full_path)
			child_proc(full_path, argv[0], tokens);
		else
			perror(argv[0]);
		free(full_path);
		free(tokens);
		prompt();
	}
	free(line);
	free(*paths);
	free(paths);
	return (0);
}
