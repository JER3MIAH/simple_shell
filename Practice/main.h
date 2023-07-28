#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* Convertion */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/*read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/*getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * Custom data structure for a singly linked list.
 * @num: Field to store a numeric value.
 * @str: Field to store a string value.
 * @next: Points to the next node in the linked list.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Custom data structure to hold pseudo-arguments
 *                   for passing into functions.
 * @arg: A string containing arguments generated from getline.
 * @argv: An array of strings generated from the argument string.
 * @path: A string representing the current command's path.
 * @argc: The count of arguments.
 * @line_count: The count of encountered errors.
 * @err_num: The error code used for exit operations.
 * @linecount_flag: A flag indicating whether to count the current input line.
 * @fname: The name of the current program file.
 * @env: A linked list representing the local copy of environment variables.
 * @environ: A custom modified copy of environment variables from the linked list 'env'.
 * @history: A linked list node representing history.
 * @alias: A linked list node representing aliases.
 * @env_changed: A flag indicating whether environment variables were changed.
 * @status: The status of the last executed command.
 * @cmd_buf: The address of the pointer to the command buffer used for chaining.
 * @cmd_buf_type: A string representing the type of command chaining (e.g., ||, &&, ;).
 * @readfd: The file descriptor from which to read line input.
 * @histcount: The count of history line numbers.
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

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 * struct builtin - Custom data structure for built-in commands
 *                  and their associated functions.
 * @type: The built-in command flag (string representation).
 * @func: Pointer to the function that implements the built-in command.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*Function Prototypes*/
int interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alphabet(int);
int my_atoi(char *);
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);
int my_history(info_t *);
int my_alias(info_t *);
int loophsh(char **);
char *_getenv(info_t *, const char *);
int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int display_env_list(info_t *);
void _inputs(char *);
int _inputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erroratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigint_handler(int);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int bfree(void **);
int is_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);
int my_strlen(char *);
int my_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char **split_string(char *, char *);
char **split_string2(char *, char);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
