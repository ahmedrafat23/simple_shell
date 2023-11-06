#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int str_to_int(char *s)
{
	int i = 0;
	unsigned long result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * err_msg - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void err_msg(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_dec(info->line_num, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->args[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int fd)
{
	int (*put)(char) = _put;
	int i, count = 0;
	unsigned int abs, curr;

	if (fd == STDERR_FILENO)
		put = _eput;
	if (input < 0)
	{
		abs = -input;
		put('-');
		count++;
	}
	else
		abs = input;
	curr = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			put('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	put('0' + curr);
	count++;

	return (count);
}

/**
 * num_conv - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *num_conv(long num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

