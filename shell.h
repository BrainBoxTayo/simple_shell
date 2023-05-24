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
#define PATH_DELIMITER "=:"
#define WORDSIZE 1024
#define LINE_DELIMETER " \n"
#define PROMPT "($)"

extern char **environ;
int num_len(int num);
void errors(char *nama, char *av, int num, int count);
char *_itoa(int num);
char *findExecutable(char *av[]);
char *_getenv(char *envname);
int _putchar(char c);
void printEnvironment(void);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
void errorpermissiondenied(char *nama, char *av, int count);
void errornotfound(char *nama, char *av, int count);
char **token_gen(char *line);
int execute(char *av[], char *nama, char *av_cpy, int count);
int comparestring(char *av[]);
int _putchare(char c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#endif
