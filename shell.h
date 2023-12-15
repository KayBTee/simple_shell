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

#endif /* SHELL_H */
