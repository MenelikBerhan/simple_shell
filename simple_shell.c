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
	/* to fix or add
	1. error message
	2. difference when using _get_line instead of getline (mentioned in _get_line in detail)
		- when ^D is typed after atleast one char (whe typed at newline it exits and is ok for our getline)

	3. ^C should not terminate the shell. It's the same as pressing enter for shell.
	4. argument parsing for (for ; #, $, &&, ||)
	5. differenciate when run from pipe or file (so as not to print prompt)
	6. inbuilts (exit, env, setenv, unsetenv, cd and alias)
	7. Cleanup for all (memory leak and code redudency)
	 */
	size_t len;
	char *line, **tokens, *full_path, **paths;
	ssize_t nread;
	int status, i_mode = isatty(STDIN_FILENO);
	pid_t child_pid;
	struct stat buf;
	extern char **environ;
	(void)argc;

	line = malloc(sizeof(char) * 1);
	memset(line, 0, 1);
	prompt();
	paths = get_path(environ);
	while ((nread = getline(&line, &len, stdin)) != -1)
	// while ((nread = _get_line(&line, &len, stdin)) != -1)
	{
		if (nread == 1 && *line == 10)
		{
			write(STDOUT_FILENO, "$ ", 2);
			continue;
		}
		if (line[nread - 1] == 10)
			line[nread - 1] = 0;
		tokens = _strtok(line, " ");
		full_path = add_path(tokens[0], paths);
		if (full_path)
		{
			tokens[0] = full_path;
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error:");
				return (1);
			}
			else if (child_pid == 0)
			{
				if (execve(tokens[0], tokens, environ) == -1)
					perror(argv[0]);
				_exit(EXIT_FAILURE);
			}
			else
			{
				if (wait(&status) != child_pid)
				{
					perror("Error:");
					return (1);
				}
			}
		}
		else
			perror(argv[0]);
		free(*tokens);
		free(tokens);
		prompt();
	}
	free(line);
	free(*paths);
	free(paths);
	return (0);
}

/**
 * parse_tokens - parses array of tokens.(for ; #, $, &&, ||)
 *
 * Return: separate commands.
 */
/* char ***parse_tokens(char **tokens)
{

} */