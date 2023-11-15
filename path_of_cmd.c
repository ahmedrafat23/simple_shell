#include "shell.h"

/**
 * if_is_cmd - determines if the file is an executable
 * @info: the info struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */

int if_is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupl_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */

char *dupl_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: PATH of string
 * @cmd: the command to find
 * Return: full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0;
	int j = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (if_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupl_chars(pathstr, j, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (if_is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			j = i;
		}
		i++;
	}
	return (NULL);
}

