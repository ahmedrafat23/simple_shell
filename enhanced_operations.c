#include "custom_shell.h"

/**
 * buffer_input - buffers chained commands
 * @shell_info: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t buffer_input(shell_info_t *shell_info, char **buffer, size_t *length)
{
    ssize_t read_bytes = 0;
    size_t length_position = 0;

    if (!*length) /* if nothing left in the buffer, fill it */
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handle_sigint);
#if USE_GETLINE
        read_bytes = getline(buffer, &length_position, stdin);
#else
        read_bytes = custom_getline(shell_info, buffer, &length_position);
#endif
        if (read_bytes > 0)
        {
            if ((*buffer)[read_bytes - 1] == '\n')
            {
                (*buffer)[read_bytes - 1] = '\0'; /* remove trailing newline */
                read_bytes--;
            }
            shell_info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(shell_info, *buffer, shell_info->histcount++);
            /* if (_strchr(*buffer, ';')) is this a command chain? */
            {
                *length = read_bytes;
                shell_info->cmd_buffer = buffer;
            }
        }
    }
    return read_bytes;
}

/**
 * receive_input - gets a line minus the newline
 * @shell_info: parameter struct
 *
 * Return: bytes read
 */
ssize_t receive_input(shell_info_t *shell_info)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t i, j, length;
    ssize_t read_bytes = 0;
    char **buffer_ptr = &(shell_info->arguments), *ptr;

    _putchar(BUF_FLUSH);
    read_bytes = buffer_input(shell_info, &buffer, &length);
    if (read_bytes == -1) /* EOF */
        return -1;
    if (length) /* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buffer position */
        ptr = buffer + i; /* get pointer for return */

        check_chain(shell_info, buffer, &j, i, length);
        while (j < length) /* iterate to semicolon or end */
        {
            if (is_chain(shell_info, buffer, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= length) /* reached end of buffer? */
        {
            i = length = 0; /* reset position and length */
            shell_info->cmd_buffer_type = CMD_NORM;
        }

        *buffer_ptr = ptr; /* pass back pointer to current command position */
        return _strlen(ptr); /* return length of current command */
    }

    *buffer_ptr = buffer; /* else not a chain, pass back buffer from custom_getline() */
    return read_bytes; /* return length of buffer from custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @shell_info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: read_bytes
 */
ssize_t read_buffer(shell_info_t *shell_info, char *buffer, size_t *i)
{
    ssize_t read_bytes = 0;

    if (*i)
        return 0;
    read_bytes = read(shell_info->readfd, buffer, READ_BUFFER_SIZE);
    if (read_bytes >= 0)
        *i = read_bytes;
    return read_bytes;
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @shell_info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @size: size of preallocated pointer buffer if not NULL
 *
 * Return: s
 */
int custom_getline(shell_info_t *shell_info, char **pointer, size_t *size)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t i, length;
    size_t k;
    ssize_t read_bytes = 0, result = 0;
    char *ptr = NULL, *new_ptr = NULL, *c;

    ptr = *pointer;
    if (ptr && size)
        result = *size;
    if (i == length)
        i = length = 0;

    read_bytes = read_buffer(shell_info, buffer, &length);
    if (read_bytes == -1 || (read_bytes == 0 && length == 0))
        return -1;

    c = _strchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : length;
    new_ptr = _realloc(ptr, result, result ? result + k : k + 1);
    if (!new_ptr) /* MALLOC FAILURE! */
        return ptr ? free(ptr), -1 : -1;

    if (result)
        _strncat(new_ptr, buffer + i, k - i);
    else
        _strncpy(new_ptr, buffer + i, k - i + 1);

    result += k - i;
    i = k;
    ptr = new_ptr;

    if (size)
        *size = result;
    *pointer = ptr;
    return result;
}

/**
 * handle_sigint - blocks ctrl-C
 * @signal_number: the signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused))int signal_number)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

