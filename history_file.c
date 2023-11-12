#include "custom_shell.h"

/**
 * obtain_history_file - gets the history file
 * @custom_info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *obtain_history_file(custom_info_t *custom_info)
{
	char *buffer, *directory;

	directory = _getenv(custom_info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * record_history - creates a file, or appends to an existing file
 * @custom_info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int record_history(custom_info_t *custom_info)
{
	ssize_t file_descriptor;
	char *filename = obtain_history_file(custom_info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);
	for (node = custom_info->command_history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * retrieve_history - reads history from file
 * @custom_info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int retrieve_history(custom_info_t *custom_info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *filename = obtain_history_file(custom_info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stats))
		file_size = file_stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			construct_history_list(custom_info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		construct_history_list(custom_info, buffer + last, line_count++);
	free(buffer);
	custom_info->histcount = line_count;
	while (custom_info->histcount-- >= HISTORY_MAX)
		delete_node_at_index(&(custom_info->command_history), 0);
	reorder_history(custom_info);
	return (custom_info->histcount);
}

/**
 * construct_history_list - adds entry to a history linked list
 * @custom_info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history line_count, histcount
 *
 * Return: Always 0
 */
int construct_history_list(custom_info_t *custom_info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (custom_info->command_history)
		node = custom_info->command_history;
	add_node_end(&node, buffer, line_count);

	if (!custom_info->command_history)
		custom_info->command_history = node;
	return (0);
}

/**
 * reorder_history - renumbers the history linked list after changes
 * @custom_info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int reorder_history(custom_info_t *custom_info)
{
	list_t *node = custom_info->command_history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (custom_info->histcount = i);
}

