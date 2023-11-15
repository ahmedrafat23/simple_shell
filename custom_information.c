#include "shell.h"

/**
 * init_custom_info - initializes custom_info_t struct
 * @info: struct address
 */
void init_custom_info(custom_info_t *info)
{
	info->arguments = NULL;
	info->argument_vector = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * configure_custom_info - initializes custom_info_t struct
 * @info: struct address
 * @arg_vector: argument vector
 */
void configure_custom_info(custom_info_t *info, char **arg_vector)
{
	int i = 0;

	info->program_name = arg_vector[0];
	if (info->arguments)
	{
		info->argument_vector = strtow(info->arguments, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->arguments);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_custom_alias(info);
		replace_custom_vars(info);
	}
}

/**
 * release_custom_info - frees custom_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void release_custom_info(custom_info_t *info, int all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->arguments);
		if (info->custom_env_list)
			free_list(&(info->custom_env_list));
		if (info->command_history)
			free_list(&(info->command_history));
		if (info->custom_alias_list)
			free_list(&(info->custom_alias_list));
		ffree(info->custom_environment);
		info->custom_environment = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}

