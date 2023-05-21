#include "main.h"

/**
 * run_comm - runs a command
 * @sh: shell name
 * @line: line input
 * @alias: alias list
 * @paths: paths array
 *
 * Return: process status
 */
int run_comm(char *sh, char *line, Alias **alias, char **paths)
{
	char *full_path, **tokens;
	int proc_status = -1, u_alias = 1;

	tokens = _strtok(line, " ");
	u_alias = check_alias(*alias, &tokens);
	proc_status = handle_inbuilts(u_alias, sh, line, paths, tokens, alias);
	if (proc_status != -1)
		return (proc_status);
	full_path = add_path(tokens[0], paths);
	if (full_path)
		proc_status = child_proc(sh, full_path, tokens);
	else
	{
		proc_status = 127;
		fprintf(stderr, "%s: 1: %s: not found\n", sh, tokens[0]);
	}
	free(full_path);
	if (!u_alias)
		free(*tokens);
	free(tokens);
	return (proc_status);
}
