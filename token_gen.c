#include "shell.h"
/**
 * token_gen - tokenizes string user inputs
 * @line: line to be tokenized
 * Return: split string
*/
char **token_gen(char *line)
{
	char **cmd = NULL;
	char *token;
	int i;

	cmd = malloc(sizeof(char *) * WORDSIZE);
	if (cmd == NULL)
	{
		exit(EXIT_FAILURE);
	}
	token = strtok(line, LINE_DELIMETER);
	i = 0;
	while (token != NULL)
	{
		cmd[i] = token;
		token = strtok(NULL, LINE_DELIMETER);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
