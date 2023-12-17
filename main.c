#include "shell.h"
/**
 * execute_command - Executes a single command
 * @info: Pointer to shell info structure
 * @cmd: Command to execute
 * Return: Exit status of the command
 */
int execute_command(shell_info_t *info, char *cmd)
{
	int status;
	pid_t child_pid;

	info->args = tokenize_command(cmd, "\n \t\r");
	if (info->args && info->args[0])
	{
		if (sib(info) == NULL)
			cep(info);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		pce(info, "Fork failed\n");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execvp(info->args[0], info->args) == -1)
		{
			pce(info, ": command not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			status = 130;
	}
	free(info->args);
	return (status);
}
/**
 * execute_commands - Executes multiple commands with logical operators
 * @info: Pointer to shell info structure
 */
void execute_commands(shell_info_t *info)
{
	size_t i;
	int result, logical_op = 1;

	for (i = 0; info->cmd_list && info->cmd_list[i] != NULL; i++)
	{
		if (logical_op == 1)
			result = execute_command(info, info->cmd_list[i]);
		else
			result = 0;
		if (info->cmd_list[i + 1] != NULL)
		{
			if (compare_custom_str(info->cmd_list[i + 1], "&&") == 0)
				logical_op = (result == 0) ? 1 : 0;
			else if (compare_custom_str(info->cmd_list[i + 1], "||") == 0)
				logical_op = (result != 0) ? 1 : 0;
			else
				logical_op = 1;
			i++;
		}
	}
}
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
