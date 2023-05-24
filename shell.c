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
	size_t count = 0, linesize = 10, status;

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, 3);
		if (_getline(&line, &linesize, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(line), fflush(STDIN_FILENO), exit(EXIT_SUCCESS);
		}
		av = token_gen(line);
		if (!av[0])
		{
			free(av);
			continue;
		}
		av_cpy = av[0];
		if (comparestring(av) == 1)
		{
			free(av);
			continue;
		}
		else if (comparestring(av) == 0)
		{
			free(av), free(line);
			exit(EXIT_SUCCESS);
		}
		count += 1;
		status = execute(av, nama, av_cpy, count);
		if (status == 1)
		{
			free(av);
			continue;
		}
		else if (status == 2)
		{
			errors(nama, av_cpy, 2, count);
			continue;
		}
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
	char *holder = NULL;

	if (((_strncmp(av[0], "./", 2)) && (_strncmp(av[0], "/", 1))))
	{
		holder = findExecutable(av);
		if (holder == NULL)
		{
			free(av);
			return (2);
		}
		av[0] = holder;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(av[0], av, environ) == -1)
		{
			free(holder);
			free(av);
			errors(nama, av_cpy, 3, count);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		free(holder);
		return (1);
	}
	return (0);
}
