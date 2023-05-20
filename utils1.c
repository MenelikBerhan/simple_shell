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
		if (s[i] >= 32 && s[i] <= 127)
			s[j++] = s[i];
	s[j] = '\0';
}

/**
 * exit_shell - handle exit commands and parameters
 * @code: optional exit code
 * @l: line string
 * @t: input tokens
 * @p: paths
 * @a: current alias list
 */
void exit_shell(char *code, char *l, char **t, char **p, Alias **a)
{
	free(t);
	free(l);
	free(*p);
	free(p);
	free_alias(*a);
	if (code)
		exit(atoi(code));
	exit(0);
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

/**
 * free_alias - frees the entire alias list
 * @head: current alias list head
 */
void free_alias(Alias *head)
{
	Alias *curr = head, *next = NULL;

	for (; curr; curr = next)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
	}
}
