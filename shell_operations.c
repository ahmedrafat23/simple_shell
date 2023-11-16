#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		init_custom_info(info);
		if (is_interactive(info))
			_puts("$ ");
		custom_putchar(BUF_FLUSH);
		r = receive_input(info);
		if (r != -1)
		{
			configure_custom_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		release_custom_info(info, 0);
	}
	write_hist(info);
	release_custom_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int k, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", ex_sh},
		{"env", (char *(*)(info_t *, const char *))get_env},
		{"help", _help},
		{"history", history_display},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", ch_dir},
		{"alias", alias_shell},
		{NULL, NULL}};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(info->argv[0], builtintbl[k].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[k].func(info);
			break;
		}
	return (built_in_ret);
}

