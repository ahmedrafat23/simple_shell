#include "custom_shell.h"

/**
 * init_custom_info - initializes custom_info_t struct
 * @custom_info: struct address
 */
void init_custom_info(custom_info_t *custom_info)
{
	custom_info->arguments = NULL;
	custom_info->argument_vector = NULL;
	custom_info->path = NULL;
	custom_info->argument_count = 0;
}

/**
 * configure_custom_info - initializes custom_info_t struct
 * @custom_info: struct address
 * @arg_vector: argument vector
 */
void configure_custom_info(custom_info_t *custom_info, char **arg_vector)
{
	int i = 0;

	custom_info->program_name = arg_vector[0];
	if (custom_info->arguments)
	{
		custom_info->argument_vector = strtow(custom_info->arguments, " \t");
		if (!custom_info->argument_vector)
		{
			custom_info->argument_vector = malloc(sizeof(char *) * 2);
			if (custom_info->argument_vector)
			{
				custom_info->argument_vector[0] = _strdup(custom_info->arguments);
				custom_info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; custom_info->argument_vector && custom_info->argument_vector[i]; i++)
			;
		custom_info->argument_count = i;

		replace_custom_alias(custom_info);
		replace_custom_vars(custom_info);
	}
}

/**
 * release_custom_info - frees custom_info_t struct fields
 * @custom_info: struct address
 * @all: true if freeing all fields
 */
void release_custom_info(custom_info_t *custom_info, int all)
{
	ffree(custom_info->argument_vector);
	custom_info->argument_vector = NULL;
	custom_info->path = NULL;
	if (all)
	{
		if (!custom_info->command_buffer)
			free(custom_info->arguments);
		if (custom_info->custom_env_list)
			free_list(&(custom_info->custom_env_list));
		if (custom_info->command_history)
			free_list(&(custom_info->command_history));
		if (custom_info->custom_alias_list)
			free_list(&(custom_info->custom_alias_list));
		ffree(custom_info->custom_environment);
			custom_info->custom_environment = NULL;
		bfree((void **)custom_info->command_buffer);
		if (custom_info->read_file_descriptor > 2)
			close(custom_info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}

