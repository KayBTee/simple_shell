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

typedef struct shell_builtin
{
	char *name;
	void (*func)(shell_info_t *);
} shell_builtin_t;

char *cstrtok_r(char *str, const char *delim);
void (*identify_builtin(shell_info_t *info))(shell_info_t *info);
void exit_shell(shell_info_t *info);
void show_shell_env(shell_info_t *info);
void set_shell_env(shell_info_t *info);
void unset_shell_env(shell_info_t *info);
char **create_shell_env(char **env_vars);
void destroy_shell_env(char **env_vars);
ssize_t print_custom_str(char *str);
char *dup_custom_str(char *str_to_dup);
int compare_custom_str(char *str1, char *str2);
char *cat_custom_str(char *str1, char *str2);
unsigned int custom_str_len(char *str);
char **tokenize_cmd(char *cmd_buf, char *delimiter);
char **realloc_custom_ptr(char **ptr, size_t *size);
void add_custom_key(shell_info_t *info);
char **find_custom_key(char **env_vars, char *key);
char *add_custom_value(char *key, char *value);
int convert_str_to_int(char *str);
void check_exec_path(shell_info_t *info);
int exec_shell_cmd(char *command, shell_info_t *info);
char *find_exec_path(char **env_vars);
int exec_current_dir(shell_info_t *info);
int check_dir_exist(char *path);
void print_custom_err(shell_info_t *info, char *msg);
void print_custom_err_msg(char *str);
char *int_to_custom_str(unsigned int value);

#endif /* SHELL_H */
