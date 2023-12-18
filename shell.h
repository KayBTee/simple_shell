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

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

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
 * allowing a uniform prototype for the function pointer struct
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
    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;
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
void set_info(info_t *info, char **);
void free_info(info_t *info, int);
ssize_t get_input(info_t *info);
void sigintHandler(int);
int build_history_list(info_t *info, char *buf, int linecount);
int write_history(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);
int replace_string(char **old, char *new);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
list_t *node_starts_with(list_t *list, char *prefix, char delimiter);
char *starts_with(const char *str, const char *prefix);

#endif /* SHELL_H */
