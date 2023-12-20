#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64
#define MAX_PATH_SIZE 1024

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
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @environ: custom modified copy of environ from LL env
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

    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
     0, 0, 0}

/**
 *struct shell_info - struct for shell info
 * @args: command line args
 * @cmd_buf: buffer for commands
 * @env_vars: Environment vars
 * @cmd_count: count of commands
 * @init_args: args at shell start
 * @exit_code: exit
 * @cmd_list: commands to execute
 */
typedef struct shell_info
{
	char **args;
	char *cmd_buf;
	char **env_vars;
	size_t cmd_count;
	char **init_args;
	int exit_code;
	char **cmd_list;
} shell_info_t;

/**
 *struct shell_builtin - structure for shell built in function
 *@name: Name of the custom builtin command
 *@func: function pointer
 */
typedef struct shell_builtin
{
	char *name;
	void (*func)(shell_info_t *);
} shell_builtin_t;

char *cstrtok_r(char *str, const char *delim);
void (*sib(shell_info_t *info))(shell_info_t *info);
void ses(shell_info_t *info);
void ssse(shell_info_t *info);
void sssev(shell_info_t *info);
void ssseu(shell_info_t *info);
char **cse(char **ev);
void dse(char **ev);
ssize_t print_custom_str(char *str);
char *dup_custom_str(char *str_to_dup);
int compare_custom_str(char *str1, char *str2);
char *cat_custom_str(char *str1, char *str2);
unsigned int custom_str_len(char *str);
char **tokenize_command(char *cmd_buf, char *delimiter);
char **rcp(char **p, size_t *s);
void ack(shell_info_t *info);
char **fck(char **ev, char *k);
char *acv(char *k, char *v);
int csti(char *s);
void cep(shell_info_t *info);
int esc(char *cmd, shell_info_t *info);
char *fep(char **ev);
int ecd(shell_info_t *info);
int cde(char *p);
void pce(shell_info_t *info, char *msg);
void pecm(char *str);
char *itcs(unsigned int v);
int myccd(shell_info_t *info);
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);
int delete_node_at_index(list_t **list, unsigned int index);
list_t *add_node_end(list_t **head, const char *str, int num);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *node_starts_with(list_t *node, char *prefix, char c);
char *starts_with(const char *haystack, const char *needle);

#endif /* SHELL_H */
