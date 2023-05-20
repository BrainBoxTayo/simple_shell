#include "shell.h"
/**
 * findExcecutable - handles the path
 * @av: line from terminal
 * Return: full path of the executable
 */
char *findExecutable(char *av[])
{
	char *path = NULL;
	char *token = NULL;
	char *path_tok = NULL;
	int returncheck;

	path = _getenv("PATH");
	token = strtok(path, PATH_DELIMITER);
	while (token != NULL)
	{
		path_tok = malloc(sizeof(char) * (strlen(token) + 1));
		path_tok = _strcpy(path_tok, token);
		path_tok = _strcat(path_tok, "/");
		path_tok = _strcat(path_tok, av[0]);
		returncheck = access(path_tok, F_OK);
		if (returncheck == 0)
		{
			free(path);
			return (path_tok);
		}
		free(path_tok);
		token = strtok(NULL, PATH_DELIMITER);		
	}
	return (NULL);
}
