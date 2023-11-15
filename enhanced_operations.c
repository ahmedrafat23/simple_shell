#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of length var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_pos = 0;

	if (!*len)
	{
	free(*buf);
	*buf = NULL;
	signal(SIGINT, handle_sigint);
#if USE_GETLINE
	read_bytes = getline(buf, &len_pos, stdin);
#else
	read_bytes = custom_getline(info, buf, &len_pos);
#endif
	if (read_bytes > 0)
	{
	if ((*buf)[read_bytes - 1] == '\n')
	{
	(*buf)[read_bytes - 1] = '\0'; /* remove trailing newline */
	read_bytes--;
	}
	info->linecount_flag = 1;
	remove_comments(*buf);
	build_history_list(info, *buf, info->histcount++);
	/* if (_strchr(*buf, ';')) is this a command chain? */
	{
	*len = read_bytes;
	info->cmd_buf = buf;
	}
	}
	}
	return (read_bytes);
}

/**
 * receive_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t receive_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **buf_ptr = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(info, &buf, &len);
	if (read_bytes == -1) /* EOF */
	return (-1);
	if (len)
	{ /* we have commands left in the chain buffer */
	j = i; /* init new iterator to current buffer position */
	ptr = buf + i; /* get pointer for return */

	check_chain(info, buf, &j, i, len);
	while (j < len)
	{ /* iterate to semicolon or end */
	if (is_chain(info, buf, &j))
	break;
	j++;
	}

	i = j + 1; /* increment past nulled ';'' */
	if (i >= len)
	{ /* reached end of buffer? */
	i = len = 0; /* reset position and length */
	info->cmd_buffer_type = CMD_NORM;
	}

	*buf_ptr = ptr; /* pass back pointer to current command position */
	return (_strlen(ptr)); /* return length of current command */
	}

	*buf_ptr = buf; /* else not a chain, pass back buffer from custom_getline() */
	return (read_bytes); /* return length of buffer from custom_getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: read_bytes
 */
ssize_t read_buf(info_t *info, char *buffer, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
	return (0);
	read_bytes = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (read_bytes >= 0)
	*i = read_bytes;
	return (read_bytes);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @size: size of preallocated pointer buffer if not NULL
 *
 * Return: s
 */
int custom_getline(info_t *info, char **ptr, size_t *size)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_bytes = 0, result = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
	result = *size;
	if (i == len)
	i = len = 0;

	read_bytes = read_buf(info, buf, &len);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
	return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, result, result ? result + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
	return (p ? (free(p), -1) : -1);

	if (result)
	_strncat(new_p, buf + i, k - i);
	else
	_strncpy(new_p, buf + i, k - i + 1);

	result += k - i;
	i = k;
	p = new_p;

	if (size)
	*size = result;
	*ptr = p;
	return (result);
}

/**
 * handle_sigint - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

