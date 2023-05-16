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
int _get_line(char **line, size_t *nread);
char **_strtok(char *str, char *delimiters);
char **get_path(char **env);
char *add_path(char *file_name, char **paths);

#endif