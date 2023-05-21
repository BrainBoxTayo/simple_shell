#include "shell.h"

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}
/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * errors - prints error messages
 * @av: argument vector
 * @nama: name of the program
 * @num: error number
 * @count: count of commands
 * Return: void
 */
void errors(char *nama, char *av, int num, int count)
{
	if (num == 2)
	{
		errorpermissiondenied(nama, av, count);
	}
	else if (num == 3)
	{
		errornotfound(nama, av, count);
	}
}
/**
 * errorpermissiondenied - prints error messages
 * @av: argument vector
 * @nama: name of the program
 * @count: count of commands
 * Return: void
 */
void errorpermissiondenied(char *nama, char *av, int count)
{
	int i;
	char *error2 = ": Permission denied\n";
	char *count_arr = _itoa(count);

	for (i = 0; nama[i] != '\0'; i++)
		_putchar(nama[i]);
	_putchar(':');
	_putchar(' ');
	for (i = 0; count_arr[i] != '\0'; i++)
		_putchar(count_arr[i]);
	_putchar(':');
	_putchar(' ');
	for (i = 0; av[i] != '\0'; i++)
		_putchar(av[i]);
	for (i = 0; error2[i] != '\0'; i++)
		_putchar(error2[i]);
	free(count_arr);
}

/**
 * errornotfound - prints error messages
 * @av: argument vector
 * @nama: name of the program
 * @count: count of commands
 * Return: void
 */
void errornotfound(char *nama, char *av, int count)
{
	int i;
	char *error3 = ": not found\n";
	char *count_arr = _itoa(count);

	for (i = 0; nama[i] != '\0'; i++)
		_putchar(nama[i]);
	_putchar(':');
	_putchar(' ');
	for (i = 0; count_arr[i] != '\0'; i++)
		_putchar(count_arr[i]);
	_putchar(':');
	_putchar(' ');
	for (i = 0; av[i] != '\0'; i++)
		_putchar(av[i]);
	for (i = 0; error3[i] != '\0'; i++)
		_putchar(error3[i]);
	free(count_arr);
}
