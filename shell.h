#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_PATH_LENGTH 1024
#define PATH_DELIMITER ":"
#define WORDSIZE 1024
#define LINE_DELIMETER " \n"
#define PROMPT "($)"
char **_getenv(const char *var);
char **token_gen(char *line);
#endif
