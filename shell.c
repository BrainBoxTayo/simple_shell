#include "shell.h"
/**
 * main - main function for shell
 * @av: argument vector
 * @ac: argument count
 * @envp: environment
 * Return: 0 on success
 */

int main(int ac, char *av[], char *envp[])
{
	char *line = NULL;
	size_t linesize = 10;
	int status;
	pid_t pid;
	int flag = 1;

	signal(SIGINT, SIG_IGN);
	while (flag == 1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, 3);
		if (getline(&line, &linesize, stdin) == -1)
			break;
		if (line == NULL)
			exit(0);
		av = token_gen(line);
		if (!av[0])
		{
			free(av);
			continue;
		}
		if (_strncmp(av[0], "exit", 4) == 0)
		{
			free(av), free(line);
			exit(0);
		}
		if (_strncmp(av[0], "env", 3) == 0)
		{
			printEnvironment();
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(av[0], av, envp) == -1)
				perror("./shell");
		}
		else if (pid > 0)
		{
			wait(&status);
		}
		free(av);
	}
	free(line);
	return (0);
}