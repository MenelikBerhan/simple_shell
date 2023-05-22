#include "main.h"

/**
 * run_comm - runs a command
 * @sh: shell name
 * @line: line input
 * @alias: alias list
 * @paths: paths array
 * @o_env_adrs: pointer to a pointer to the original environ.
 * @o_env_elms: pointer to an array of original environ elements address.
 *
 * Return: process status
 */
int run_comm(char *sh, char *line, Alias **alias, char **paths,
							char **o_env_adrs, char **o_env_elms)
{
	char *full_path, **tokens;
	int proc_status = -1;

	tokens = _strtok(line, " ");
	check_alias(*alias, &tokens);
	proc_status = handle_inbuilts(sh, line, paths, tokens, alias,
									o_env_adrs, o_env_elms);
	if (proc_status != -2)
		return (proc_status);
	full_path = add_path(tokens[0], paths);
	if (full_path)
		proc_status = child_proc(sh, full_path, tokens);
	else
	{
		proc_status = 127;
		fprintf(stderr, "%s: 1: %s: not found\n", sh, tokens[0]);
	}
	free(tokens);
	return (proc_status);
}
