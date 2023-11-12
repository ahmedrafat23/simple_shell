#include "custom_shell.h"

/**
 * insert_list_node - inserts a node at the beginning of the list
 * @list_head: address of pointer to list head
 * @content: content field of the node
 * @index: node index used by history
 *
 * Return: size of the list
 */
list_t *insert_list_node(list_t **list_head, const char *content, int index)
{
	list_t *new_head;

	if (!list_head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->index = index;
	if (content)
	{
		new_head->content = _strdup(content);
		if (!new_head->content)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *list_head;
	*list_head = new_head;
	return (new_head);
}

/**
 * append_list_node - appends a node to the end of the list
 * @list_head: address of pointer to list head
 * @content: content field of the node
 * @index: node index used by history
 *
 * Return: size of the list
 */
list_t *append_list_node(list_t **list_head, const char *content, int index)
{
	list_t *new_node, *node;

	if (!list_head)
		return (NULL);

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (content)
	{
		new_node->content = _strdup(content);
		if (!new_node->content)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}

/**
 * print_list_content - prints only the content element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list_content(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->content ? h->content : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_node_at_index - deletes a node at the given index
 * @list_head: address of pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **list_head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!index)
	{
		node = *list_head;
		*list_head = (*list_head)->next;
		free(node->content);
		free(node);
		return (1);
	}
	node = *list_head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->content);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * clear_list - frees all nodes of a list
 * @list_head_ptr: address of pointer to the list head
 *
 * Return: void
 */
void clear_list(list_t **list_head_ptr)
{
	list_t *node, *next_node, *head;

	if (!list_head_ptr || !*list_head_ptr)
		return;
	head = *list_head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->content);
		free(node);
		node = next_node;
	}
	*list_head_ptr = NULL;
}

