#include "shell.h"
/**
 * _realloc - Reallocates a memoryory block using malloc and free.
 * @ptr: A pointer to the memoryory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memoryory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memoryory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memory;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
			return (NULL);
		return (memory);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptr_copy = ptr;
	memory = malloc(sizeof(*ptr_copy) * new_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}
	filler = memory;
	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;
	free(ptr);
	return (memory);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string we assign to lineptr.
 * @b: The size of the buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t retrnval;
	char c = 'x', *buffer;
	int readno;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);
	while (c != '\n')
	{
		readno = read(STDIN_FILENO, &c, 1);
		if (readno == -1 || (readno == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (readno == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';
	assign_lineptr(lineptr, n, buffer, input);
	retrnval = input;
	if (readno != 0)
		input = 0;
	return (retrnval);
}
