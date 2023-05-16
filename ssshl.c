#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
/*
 *execve helps to execute programs
 * first arg is filename, second is argument, third is envp
 * hmm
 */
char **environ;
int main(void)
{
	int flag = 1;
	while (flag == 1)
	{
		size_t argc = 0;
		int i = 0;/*increment in variable for the strtok to argv*/
		char *line = NULL, *token = NULL;
		char *delim = " \n";
		pid_t pid1;
		size_t j = 10;/*malloc var for getline*/
		char **argv;

		printf("$:) ");/*prompt*/
		if (getline(&line, &j, stdin) == -1)
			perror("Error\n");
		if (line == NULL)
			free(line);
		else
		{
			/*count number of arguments passed*/			
			token = strtok(line, delim);
			while (token)
			{
				token = strtok(NULL, delim);
				argc++;
			}
			argv = malloc(sizeof(char *) * argc);
			token = strtok(line, delim);
			while (token)
			{
				argv[i] = token;
				token = strtok(NULL, delim);
				i++;
			}
			pid1 = fork();
			if (pid1 == 0)
			{
				if (execve(argv[0], argv, environ) == -1)
					perror("./shell");
			}
			else if (pid1 > 0)
			{
				wait(NULL);				
				continue;
			}			
		}
		free(argv), free(line);
		}
	return (0);
}