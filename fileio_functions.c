#include "shell.h"

/**
 * custom_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_putchar(str[index]);
		index++;
	}
}

/**
 * custom_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int custom_putchar(char c)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;
	return (1);
}

/**
 * custom_fdput - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int custom_fdput(char c, int fd)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;
	return (1);
}

/**
 * custom_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: Returns the number of characters put.
 */
int custom_putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		char_count += custom_fdput(*str++, fd);
	}
	return (char_count);
}

