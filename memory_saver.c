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

/**
 * free_list - delete all the list
 * @node: pointer to the first node
 */

void free_list(node *head)
{
	node *current = head;
	node *nextNode;

	while (current != NULL)
	{
		nextNode = current->next;
		free(current->num);
		free(current->str);
		free(current);
		current = nextNode;
	}
}

