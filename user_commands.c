#include "shell.h"

/**
 * ex_sh - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int ex_sh(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = str_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			err_msg(info, "Illegal number: ");
			custom_puts(info->argv[1]);
			custom_putchar('\n');
			return (1);
		}
		info->err_num = str_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * ch_dir - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ch_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		err_msg(info, "can't cd to ");
		custom_puts(info->argv[1]), custom_putchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

