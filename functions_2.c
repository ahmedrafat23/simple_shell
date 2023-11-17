#include "shell.h"

/**
 * list_len - length of linked list
 * @node: pointer to first node
 * Return: size of list
 */

size_t list_len(const list_t *node)
{
	size_t n = 0;

	while (node)
	{
		node = node->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->content) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->content);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = starts_with(node->content, prefix);
		if (s && ((c == -1) || (*s == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * print_list - prints all elements of the linked list
 * @h: pointer to first node
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		char *converted = convert_number(h->content, 10, 0);
		_puts(converted);
		_putchar(':');
		_putchar(' ');
		_puts(h->content ? h->content : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

