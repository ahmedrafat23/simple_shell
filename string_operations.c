#include "shell.h"

/**
 **copy_string - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@num_chars: the number of characters to be copied
 *Return: the concatenated string
 */
char *copy_string(char *destination, char *source, int num_chars)
{
	int d_index = 0, s_index = 0;
	char *result = destination;

	while (source[s_index] != '\0' && d_index < num_chars - 1)
	{
		destination[d_index] = source[s_index];
		d_index++;
		s_index++;
	}

	if (d_index < num_chars)
	{
		int j = d_index;
		while (j < num_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}

	return result;
}

/**
 **concat_strings - concatenates two strings
 *@first_str: the first string
 *@second_str: the second string
 *@max_chars: the maximum number of characters to be used
 *Return: the concatenated string
 */
char *concat_strings(char *first_str, char *second_str, int max_chars)
{
	int f_index = 0, s_index = 0;
	char *result = first_str;

	while (first_str[f_index] != '\0')
		f_index++;

	while (second_str[s_index] != '\0' && s_index < max_chars)
	{
		first_str[f_index] = second_str[s_index];
		f_index++;
		s_index++;
	}

	if (s_index < max_chars)
		first_str[f_index] = '\0';

	return result;
}

/**
 **find_char - locates a character in a string
 *@str_to_search: the string to be searched
 *@char_to_find: the character to look for
 *Return: (str_to_search) a pointer to the memory area str_to_search
 */
char *find_char(char *str_to_search, char char_to_find)
{
	do {
		if (*str_to_search == char_to_find)
			return str_to_search;
	} while (*str_to_search++ != '\0');

	return NULL;
}

