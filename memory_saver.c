#include "shell.h"

/**
 * _free - frees the pointer and NULLs the address
 * @ptr: address of the pointer
 * Return: 1 if freed, if fails 0
 */

int _free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
