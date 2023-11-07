#include "shell.h"

/**
 * custom_strncpy - copies a string
 *
 * @dest_str: the destination string to be copied to
 * @src_str: the source string
 * @n_chars: the number of characters to be copied
 *
 * Return: the concatenated string
 */
char *custom_strncpy(char *dest_str, char *src_str, int n_chars)
{
	int index_dest = 0, index_src = 0;
	char *result = dest_str;

	while (src_str[index_src] != '\0' && index_dest < n_chars - 1)
	{
		dest_str[index_dest] = src_str[index_src];
		index_dest++;
		index_src++;
	}

	if (index_dest < n_chars)
	{
		int j = index_dest;
		while (j < n_chars)
		{
			dest_str[j] = '\0';
			j++;
		}
	}

	return (result);
}

/**
 * custom_strncat - concatenates two strings
 *
 * @dest_str: the first string
 * @src_str: the second string
 * @n_chars: the maximum number of characters to be used
 *
 * Return: the concatenated string
 */
char *custom_strncat(char *dest_str, char *src_str, int n_chars)
{
	int index_dest = 0, index_src = 0;
	char *result = dest_str;

	while (dest_str[index_dest] != '\0')
		index_dest++;

	while (src_str[index_src] != '\0' && index_src < n_chars)
	{
		dest_str[index_dest] = src_str[index_src];
		index_dest++;
		index_src++;
	}

	if (index_src < n_chars)
	{
		dest_str[index_dest] = '\0';
	}

	return (result);
}

/**
 * custom_strchr - locates a character in a string
 *
 * @str_to_search: the string to be searched
 * @char_to_find: the character to look for
 *
 * Return: (str_to_search) a pointer to the memory area str_to_search
 */
char *custom_strchr(char *str_to_search, char char_to_find)
{
	do {
		if (*str_to_search == char_to_find)
		{
			return (str_to_search);
		}
	} while (*str_to_search++ != '\0');

	return (NULL);
}

