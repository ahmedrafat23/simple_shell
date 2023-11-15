#include "shell.h"

/**
 * is_interactive - returns true if shell is in interactive mode
 * @i: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *i)
{
	return (isatty(STDIN_FILENO) && i->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to check
 * @d: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *d)
{
	while (*d)
	if (*d++ == c)
	return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int str_to_int(char *s)
{
	int i, sg = 1, f = 0, out;
	unsigned int r = 0;

	for (i = 0; s[i] != '\0' && f != 2; i++)
	{
	if (s[i] == '-')
	sg *= -1;

	if (s[i] >= '0' && s[i] <= '9')
	{
	f = 1;
	r *= 10;
	r += (s[i] - '0');
	}
	else if (f == 1)
	f = 2;
	}

	if (sg == -1)
	out = -r;
	else
	out = r;

	return (out);
}

