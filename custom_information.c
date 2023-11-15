#include "shell.h"

/**
 * init_custom_info - initializes custom_info_t struct
 * @info: struct address
 */
void init_custom_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * configure_custom_info - initializes custom_info_t struct
 * @info: struct address
 * @arg_vector: argument vector
 */
void configure_custom_info(info_t *info, char **arg_vector)
{
	int i = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_custom_alias(info);
		replace_custom_vars(info);
	}
}

/**
 * release_custom_info - frees custom_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void release_custom_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

