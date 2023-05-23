#include "shell.h"
/**
 * main - simple UNIX command line interpreter
 * @av: argument vector
 * @ac: argument count
 * Return: 0 on success
 */

int main(__attribute__((unused)) int ac, char *av[])
{
	char *nama = av[0], *av_cpy, *line = NULL;
	size_t count = 0, linesize = 10;

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, 3);
		if (getline(&line, &linesize, stdin) == -1)
		{
			fflush(STDIN_FILENO);
			_putchar('\n');
			exit(0);
		}
		av = token_gen(line);
		if (!av[0])
		{
			free(av);
			continue;
		}
		av_cpy = av[0];
		if (comparestring(av) == 1)
			continue;
		else if (comparestring(av) == 0)
		{
			free(av);
			exit(0);
		}
		count += 1;
		if (execute(av, nama, av_cpy, count) == 1)
			continue;
		else if (execute(av, nama, av_cpy, count) == 2)
		{
			free(av);
			errors(nama, av_cpy, 2, count);
			continue;
		}
		free(line);
	}
	return (0);
}
/**
 * comparestring - compares strings for builtins
 * @av: argument vector
 * Return: 1 if we want the program to continue
 * 0 if we want to exit
 * 2 on error
 */

int comparestring(char *av[])
{
	if (_strncmp(av[0], "exit", 4) == 0)
	{
		return (0);
	}
	if (_strncmp(av[0], "env", 3) == 0)
	{
		printEnvironment();
		return (1);
	}
	return (2);
}

/**
 * execute - handles execution of the programmes passed
 * @av: container for arguments
 * @nama: name of the program
 * @av_cpy: copy of av[0]
 * @count: count of commands
 * Return: 1 for the main programme
 * 2 if the command is not found
 * 0 on error
 */
int execute(char *av[], char *nama, char *av_cpy, int count)
{
	pid_t pid;
	int status;

	if (((_strncmp(av[0], "./", 2)) && (_strncmp(av[0], "/", 1))))
	{
		av[0] = findExecutable(av);
		if (av[0] == NULL)
		{
			return (2);
		}
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(av[0], av, environ) == -1)
		{
			free(av);
			errors(nama, av_cpy, 3, count);
			exit(0);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		return (1);
	}
	free(av);
	return (0);
}
