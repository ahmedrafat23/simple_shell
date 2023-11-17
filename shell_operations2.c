#include "shell.h"

/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_env(info, "Permission denied\n");
		}
	}
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int j, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, k = 0; info->arg[j]; j++)
		if (!is_delim(info->arg[j], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((is_interactive(info) || getenv(info, "PATH=") || info->argv[0][0] == '/')
		&& if_is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_env(info, "not found\n");
		}
	}
}

