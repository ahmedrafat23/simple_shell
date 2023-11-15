#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * ch_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */

void ch_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * re_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1
 */

int re_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * re_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1
 */

int re_alias(info_t *info)
{
	int i = 0;
	list_t *node;
	char *c;

	while (i < 10)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		c = custom_strchr(node->str, '=');
		if (!c)
			return (0);
		c = _strdup(c + 1);
		if (!c)
			return (0);
		info->argv[0] = c;
		i++;
	}
	return (1);
}

/**
 * re_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1
 */

int re_vars(info_t *info)
{
	int k = 0;
	list_t *node;

	while (info->argv[k])
	{
		if (info->argv[k][0] != '$' || !info->argv[k][1])
			continue;
		if (!_strcmp(info->argv[k], "$?"))
		{
			re_string(&(info->argv[k]),
						   _strdup(num_conv(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[k], "$$"))
		{
			re_string(&(info->argv[k]),
						   _strdup(num_conv(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[k][1], '=');
		if (node)
		{
			re_string(&(info->argv[k]),
						   _strdup(custom_strchr(node->str, '=') + 1));
			continue;
		}
		re_string(&info->argv[k], _strdup(""));
		k++;
	}
	return (0);
}

