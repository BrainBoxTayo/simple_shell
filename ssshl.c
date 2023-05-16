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
int main(int argc, char **argv)
{
	int flag = 1;
	do
	{
		if (argc == 1)
		{
			while (flag)
			{
				size_t arg_count = 0;
				int i = 0; /*increment in variable for the strtok to argv*/
				char *line = NULL, *line_cpy = NULL, *token = NULL;
				char *delim = " \n";
				pid_t pid1;
				size_t j = 10; /*malloc var for getline*/
				char **arg_v;

				printf("$:) "); /*prompt*/
				ssize_t line_size = getline(&line, &j, stdin);
				if (line_size == -1)
				{
					perror("Error");
					continue;
				}
				if (line_size == 1)
				{
					free(line);
					continue;
				}

				line_cpy = strdup(line);
				/*count number of arguments passed*/
				token = strtok(line_cpy, delim);
				while (token)
				{
					arg_count++;
					token = strtok(NULL, delim);
				}
				arg_v = malloc(sizeof(char *) * (argc + 1));
				token = strtok(line, delim);
				while (token)
				{
					arg_v[i] = token;
					token = strtok(NULL, delim);
					i++;
				}
				pid1 = fork();
				if (pid1 == 0)
				{
					if (execve(arg_v[0], arg_v, environ) == -1)
						perror("./shell");
				}
				else if (pid1 > 0)
				{
					wait(NULL);
					continue;
				}

				free(arg_v), free(line);
			}
		}
		else
		{
			pid_t pid1 = fork();
			if (pid1 == 0)
			{
				if (execve(argv[1], argv, environ) == -1)
					perror("./shell");
			}
			else if (pid1 > 0)
			{
				wait(NULL);
				flag = 2;
			}
		}
	} while (flag == 1);
	return (0);
}
