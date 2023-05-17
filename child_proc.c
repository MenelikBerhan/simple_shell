#include "main.h"

/**
 * child_proc - creates and executes a child process
 * @path: command full path
 * @sh: shell name
 * @tokens: input tokens
 *
 * Return: 0 on success, -1 on failure
 */
int child_proc(char *path, char *sh, char **tokens)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
			perror(sh);
		_exit(EXIT_FAILURE);
	}
	else
	{
		if (wait(&status) != child_pid)
		{
			perror("Error:");
			return (-1);
		}
	}
	return (0);
}
