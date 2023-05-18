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
extern char *sh;

int _get_line(char **line, FILE *fp);
char **_strtok(char *str, char *delimiters);
char **get_path(char **env);
char *add_path(char *file_name, char **paths);
int child_proc(char *sh, char *path, char **tokens);
void exit_shell(char *code, char *l, char **t, char **p);
int handle_inbuilts(char *sh, char *l, char **p, char **t);
void changedir(char *sh, char **tokens);
void handleSigInt(int signum);
void trim_in(char *s);
void prompt(void);

#endif
