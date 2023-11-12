#include "shell.h"

/**
 * _strncpy - copies a string
 *
 * @dest: the destination string to be copied to
 * @src: the source
 *
 * Return: pointer to distination
 */
char *_strncpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
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

