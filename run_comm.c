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
	int proc_status = -1, u_alias = 1;
	static int err_no = 1;

	tokens = _strtok(line, " ");
	u_alias = check_alias(*alias, &tokens);
	proc_status = handle_inbuilts(u_alias, sh, line, paths, tokens, alias,
								  o_env_adrs, o_env_elms);
	if (proc_status != -2)
	{
		if (proc_status)
		{
			if (!u_alias)
				free(*tokens);
			free(tokens);
		}
		return (proc_status);
	}
	full_path = add_path(tokens[0], paths);
	if (full_path && paths)
		proc_status = child_proc(sh, full_path, tokens);
	else
	{
		proc_status = 127;
		fprintf(stderr, "%s: %d: %s: not found\n", sh, err_no, tokens[0]);
		err_no++;
	}
	free(full_path);
	if (!u_alias)
		free(*tokens);
	free(tokens);
	return (proc_status);
}
