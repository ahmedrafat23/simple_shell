#include "shell.h"

/**
 * print_env - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int print_env(info_t *info)
{
	print_list(info->env);
	return (0);
}

/**
 * get_env - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = starts_with(node->content, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Initializes a new environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (setenv(info->argv[1], info->argv[2], 1))

		return (0);
	return (1);
}

/**
 * unset_env - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetenv(info->argv[i]);

	return (0);
}

/**
 * pop_env - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int pop_env(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_list_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}

