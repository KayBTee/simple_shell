#include "shell.h"
/**
 * sh - Handles ^C signal interrupt
 * @uv: Unused variable (required for signal function prototype)
 */
static void sh(int uv)
{
	unsigned int sf = 0;
	(void)uv;

	if (sf == 0)
		print_custom_str("\n$ ");
	else
		print_custom_str("\n");
}
/**
 * main - Main function for the custom shell
 * @ac: Number of arguments passed to main
 * @av: Array of arguments passed to main
 * @env: Array of environment variables
 * Return: 0 or exit status, or ?
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	size_t bl = 0;
	unsigned int ip = 0, i;
	shell_info_t info = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	info.init_args = av;
	info.env_vars = cse(env);
	signal(SIGINT, sh);
	if (!isatty(STDIN_FILENO))
		ip = 1;
	if (ip == 0)
		print_custom_str("$ ");
	while (getline(&(info.cmd_buf), &bl, stdin) != -1)
	{
		info.cmd_count++;
		info.cmd_list = tokenize_command(info.cmd_buf, ";");
		for (i = 0; info.cmd_list && info.cmd_list[i] != NULL; i++)
		{
			info.args = tokenize_command(info.cmd_list[i], "\n \t\r");
			if (info.args && info.args[0])
			{
				if (sib(&info) == NULL)
					cep(&info);
			}
			free(info.args);
		}
		free(info.cmd_buf);
		free(info.cmd_list);
		if (ip == 0)
			print_custom_str("$ ");
		info.cmd_buf = NULL;
	}
	if (ip == 0)
		print_custom_str("\n");
	dse(info.env_vars);
	free(info.cmd_buf);
	exit(info.exit_code);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * starts_with - check if a string starts with a specified prefix
 * @str: the string to check
 * @prefix: the prefix to check for
 * Return: a pointer to the beginning of the prefix in str if found, NULL otherwise
 */
char *starts_with(const char *str, const char *prefix)
{
    size_t prefix_len = strlen(prefix);
    size_t str_len = strlen(str);

    if (str_len < prefix_len) {
        return (NULL);
    }
    if (strncmp(str, prefix, prefix_len) == 0) {
        return (char *)str;
    }
    return (NULL);
}
