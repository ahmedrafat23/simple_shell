
#include "shell.h"

/**
 * **d_strtow - splits a string into words
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings
 */

char **d_strtow(char *str, char *d)
{
	int i, j, k, x, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			s[j][x] = str[i++];
		s[j][x] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings
 */
char **strtow(char *str, char d)
{
	int i, j, k, z, numwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);

	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (z = 0; z < k; z++)
			c[j][z] = str[i++];
		c[j][z] = 0;
	}
	c[j] = NULL;
	return (c);
}
