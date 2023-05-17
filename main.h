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

#define BUFFER_SIZE 256
extern char **environ;

int _get_line(char **line, size_t *nread, FILE *stream);
char **_strtok(char *str, char *delimiters);
char **get_path(char **env);
char *add_path(char *file_name, char **paths);
int child_proc(char *path, char *sh, char **tokens);
void exit_shell(char *code, char *l, char **t, char **p);
void handleSigInt(int signum);
void trim_in(char *s);
void prompt(void);

#endif
