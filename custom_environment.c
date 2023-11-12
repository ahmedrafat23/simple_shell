#include "custom_shell.h"

/**
 * get_custom_environment - returns the string array copy of our custom environment
 * @custom_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_custom_environment(custom_info_t *custom_info)
{
	if (!custom_info->env_array || custom_info->env_changed)
	{
	custom_info->env_array = list_to_strings(custom_info->custom_env_list);
	custom_info->env_changed = 0;
	}

	return (custom_info->env_array);
}

/**
 * remove_custom_env_var - Remove a variable from the custom environment
 * @custom_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var_name: the variable name to be removed
 */
int remove_custom_env_var(custom_info_t *custom_info, char *var_name)
{
	list_t *node = custom_info->custom_env_list;
	size_t index = 0;
	char *p;

	if (!node || !var_name)
	return (0);

	while (node)
	{
	p = starts_with(node->str, var_name);
	if (p && *p == '=')
	{
	custom_info->env_changed = delete_node_at_index(&(custom_info->custom_env_list), index);
	index = 0;
	node = custom_info->custom_env_list;
	continue;
	}
	node = node->next;
	index++;
	}
	return (custom_info->env_changed);
}

/**
 * set_custom_env_var - Initialize a new custom environment variable,
 *             or modify an existing one
 * @custom_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var_name: the variable name
 * @var_value: the variable value
 *  Return: Always 0
 */
int set_custom_env_var(custom_info_t *custom_info, char *var_name, char *var_value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var_name || !var_value)
	return (0);

	buffer = malloc(_strlen(var_name) + _strlen(var_value) + 2);
	if (!buffer)
	return (1);
	_strcpy(buffer, var_name);
	_strcat(buffer, "=");
	_strcat(buffer, var_value);
	node = custom_info->custom_env_list;
	while (node)
	{
	p = starts_with(node->str, var_name);
	if (p && *p == '=')
	{
	free(node->str);
	node->str = buffer;
	custom_info->env_changed = 1;
	return (0);
	}
	node = node->next;
	}
	add_node_end(&(custom_info->custom_env_list), buffer, 0);
	free(buffer);
	custom_info->env_changed = 1;
	return (0);
}

