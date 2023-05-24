#include "shell.h"
/**
 * _getenv - gets environment var
 * @envname: argument vector
 * Return: 0 on success
 */
char *_getenv(char *envname)
{
	int i = 0;
	char *env_cpy = NULL;

	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], envname, _strlen(envname)) == 0)
		{
			env_cpy = malloc(sizeof(char) * (_strlen(environ[i]) + 1));
			if (!env_cpy)
			{
				free(env_cpy);
				return (NULL);
			}
			_strcpy(env_cpy, environ[i]);
			return (env_cpy);
		}
		i++;
	}
	return (NULL);
}
