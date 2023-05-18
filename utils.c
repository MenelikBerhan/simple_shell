#include "main.h"

/**
 * handleSigInt - sets the interrupted variable
 * @signum: signal number
 */
void handleSigInt(int signum)
{
	(void)signum;
	printf("\n");
	prompt();
}

/**
 * trim_in - remove the '\a' char from the input string
 * @s: string to be trimmed
 */
void trim_in(char *s)
{
	int len = strlen(s), i, j = 0;

	for (i = 0; i < len; i++)
		if (s[i] != 7)
			s[j++] = s[i];
	s[j] = '\0';
}

/**
 * exit_shell - handle exit commands and parameters
 * @code: optional exit code
 * @l: line string
 * @t: input tokens
 * @p: paths
 */
void exit_shell(char *code, char *l, char **t, char **p)
{
	int exit_status = 0;

	if (code)
		exit_status = atoi(code);

	if (l)
		free(l);
	if (t)
	{
		free(*t);
		free(t);
	}
	if (p)
	{
		free(*p);
		free(p);
	}
	exit(exit_status);
}

/**
 * prompt - displays a prompt when in interactive mode
 */
void prompt(void)
{
	int i_mode = isatty(STDIN_FILENO);

	if (i_mode)
		write(STDOUT_FILENO, "$ ", 2);
}
