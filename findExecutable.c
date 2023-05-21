#include "shell.h"
/**
 * findExecutable-handles the path
 * @av: line from terminal
 * Return: full path of the executable
 */
char *findExecutable(char *av[])
{
	char *path = NULL;
	char *token = NULL;
	char *path_tok = NULL;
	int retrncheck;

	path = _getenv("PATH");
	token = strtok(path, PATH_DELIMITER);
	while (token != NULL)
	{
		path_tok = malloc(sizeof(char) * (_strlen(token) + _strlen(av[0]) + 2));
		if (!path_tok)
			return (NULL);
		path_tok = _strcpy(path_tok, token);
		path_tok = _strcat(path_tok, "/");
		path_tok = _strcat(path_tok, av[0]);
		retrncheck = access(path_tok, F_OK);
		if (retrncheck == 0)
		{
			free(path);
			return (path_tok);
		}
		free(path_tok);
		token = strtok(NULL, PATH_DELIMITER);
	}
	free(path);
	return (NULL);
}
