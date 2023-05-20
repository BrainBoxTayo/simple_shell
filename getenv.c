#include "shell.h"
/**
 * _getenv - gets environment var
 * @envname: argument vector
 * Return: 0 on success
 */
char *_getenv(char *envname)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], envname, _strlen(envname)) == 0)
		{
			return (environ[i]);
		}
		i++;
	}
	return (NULL);
}
