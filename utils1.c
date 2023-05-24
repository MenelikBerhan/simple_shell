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
		if (s[i] >= 32 || s[i] == 10)
			s[j++] = s[i];
	s[j] = '\0';
}

/**
 * exit_shell - handle exit commands and parameters
 * @u_a: is command an alias
 * @l: line string
 * @t: input tokens
 * @p: paths
 * @a: current alias list
 * @o_env_adrs: pointer to a pointer to the original environ.
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 */
void exit_shell(int u_a, char *l, char **t, char **p, Alias **a,
				char **o_env_adrs, char **o_env_elms)
{
	int c = 0;

	if (t[1])
		c = atoi(t[1]);
	if (!u_a)
		free(*t);
	free_environ(-1, o_env_adrs, o_env_elms);
	free(t);
	free(l);
	free(*p);
	free(p);
	free_alias(*a);
	exit(c);
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
