#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 256

extern char **environ;
/**
 * struct alias - struct for alias nodes
 * @key: alias key
 * @value: alias value
 * @next: next alias key-value pair
 *
 * Description: This struct holds the key-value pair of an alias
 */
typedef struct alias
{
	char *key;
	char *value;
	struct alias *next;
} Alias;

int handle_inbuilts(int u_a, char *sh, char *l, char **p, char **t, Alias **a,
								char **o_env_adrs, char **o_env_elms);
void exit_shell(int u_a, char *code, char *l, char **t, char **p, Alias **a,
								char **o_env_adrs, char **o_env_elms);
void multi_comms(char *sh, char *line, Alias **alias, char **paths,
								char **o_env_adrs, char **o_env_elms);
int run_comm(char *sh, char *line, Alias **alias, char **paths,
								char **o_env_adrs, char **o_env_elms);
int _alias(char *sh, char **t, Alias **alias_list);
int child_proc(char *sh, char *path, char **t);
char *add_path(char *file_name, char **paths);
char **_strtok(char *str, char *delimiters);
Alias *search_alias(Alias *dict, char *key);
int check_alias(Alias *a, char ***t);
int _get_line(char **line, FILE *fp);
int changedir(char *sh, char **t, char **o_env_elms);
void handleSigInt(int signum);
void free_alias(Alias *head);
int count_tokens(char **arr);
char **get_path(char **env);
void trim_in(char *s);
void prompt(void);
void _env(void);
int set_unset_env(char **tokens, char **o_env_elms);
int _setenv(const char *name, const char *value, int overwrite,
													char **o_en_el);
int _unsetenv(const char *name, char **o_env_elms);
int free_environ(int index, char **o_env_adrs, char **o_env_elms);
int _getindex(const char *name, char **envptr);
int _get_null_index(void);
char *_getenv(const char *name);

#endif
