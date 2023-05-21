#include "main.h"

/**
 * child_proc - creates and executes a child process
 * @sh: shell name
 * @path: command full path
 * @t: input tokens
 *
 * Return: 0 on success, -1 on failure
 */
int child_proc(char *sh, char *path, char **t)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(path, t, environ) == -1)
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
		return (status);
	}
	return (0);
}
