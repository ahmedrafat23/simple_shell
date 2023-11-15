#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string from getline containing arguements
 * @argv:an array of strings from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, \
	NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0 }

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* shell_operations.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* shell_operations2.c */
void fork_cmd(info_t *);
void find_cmd(info_t *);

/* path_of_cmd.c */
int if_is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* fileio_functions.c */
void custom_puts(char *);
int custom_putchar(char);
int custom_fdput(char c, int fd);
int custom_putsfd(char *str, int fd);

/* string_operations.c */
char *_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* string_operations2.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_operations3.c */
char *_strdup(const char *);
char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);

/* tokenization.c */
char **d_strtow(char *, char *);
char **strtow(char *, char);

/* reallocate.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, int, int);

/* memory_saver.c */
int _free(void **);

/* common_operations.c */
int is_interactive(info_t *);
int is_delim(char, char *);
int is_alpha(int);
int str_to_int(char *);

/* number_converter.c */
int str_to_int(char *);
void err_msg(info_t *, char *);
int print_dec(int, int);
char *num_conv(long int, int, int);
void rm_comments(char *);

/* user_commands.c */
int ex_sh(info_t *);
int ch_dir(info_t *);
int _help(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/**
 *
 * toem_getline.c
*/

/*ssize_t get_input(info_t *);*/
ssize_t buffer_input(info_t, char, size_t);

/*int _getline(info_t *, char **, size_t *);*/
ssize_t receive_input(info_t *info);

void sigintHandler(int);

/* custom_information.c */
void init_custom_info(info_t *);
void configure_custom_info(info_t *, char **);
void release_custom_info(info_t *, int);

/* env_management.c */
char *get_env(info_t *, const char *);
int print_env(info_t *);
int set_env(info_t *);
int unset_env(info_t *);
int pop_env(info_t *);

/* custom_environment.c */
char **get_environment(info_t *);
int unset_environment(info_t *, char *);
int set_environment(info_t *, char *, char *);

/* history_file.c */
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* star_link.c */
list_t *insert_list_node(list_t **, const char *, int);
list_t *append_list_node(list_t **, const char *, int);
size_t print_list_content(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void clear_list(list_t **);

/* functions_2.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t print_list(const list_t *);

/* variables.c */
int is_chain(info_t *, char *, size_t *);
void ch_chain(info_t *, char *, size_t *, size_t, size_t);
int re_string(char **, char *);
int re_alias(info_t *);
int re_vars(info_t *);

#endif

