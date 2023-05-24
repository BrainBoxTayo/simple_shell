#include "shell.h"

/**
 * _putchare - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchare(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}
