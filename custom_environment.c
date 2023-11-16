#include "shell.h"

/**
 * get_environment - returns the string array copy of our environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environment - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_environment(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->content, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_environment - Initialize a new environment variable,
 *                   or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int set_environment(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	append_list_node(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

