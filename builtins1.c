#include "shell.h"

/**
 * sib - checks if command is builtin
 * @info: shell info structure
 * Return: pointer to function
 */
void (*sib(shell_info_t *info))(shell_info_t *info)
{
	unsigned int i;
	shell_builtin_t sb[] = {
		{"exit", ses},
		{"env", ssse},
		{"setenv", sssev},
		{"unsetenv", ssseu},
		{NULL, NULL}
	};
	for (i = 0; sb[i].func != NULL; i++)
	{
		if (compare_custom_str(info->args[0], sb[i].name) == 0)
			break;
	}
	if (sb[i].func != NULL)
		sb[i].func(info);
	return (sb[i].func);
}
/**
 * ses - exits shell
 * @info: shell info
 */
void ses(shell_info_t *info)
{
	int s;

	if (compare_custom_str(info->args[0], "exit") == 0 && info->args[1] != NULL)
	{
		s = csti(info->args[1]);
		if (s == -1)
		{
			info->exit_code = 2;
			pce(info, ": Illegal number: ");
			pecm(info->args[1]);
			pecm("\n");
			free(info->cmd_list);
			info->cmd_list = NULL;
			return;
		}
		info->exit_code = s;
	}
	else if (info->args[1] != NULL)
	{
		info->exit_code = csti(info->args[1]);
		if (info->exit_code == -1)
		{
			pce(info, ": Illegal number: ");
			pecm(info->args[1]);
			pecm("\n");
			info->exit_code = 2;
		}
	}
	free(info->cmd_buf);
	free(info->args);
	free(info->cmd_list);
	dse(info->env_vars);
	exit(info->exit_code);
}
/**
 * ssse - print shell environment
 * @info: shell info
 */
void ssse(shell_info_t *info)
{
	unsigned int i = 0;

	while (info->env_vars[i])
	{
		print_custom_str(info->env_vars[i]);
		print_custom_str("\n");
		i++;
	}
	info->exit_code = 0;
}
/**
 * sssev - create new environment variable
 * @info: points to shell info
 */
void sssev(shell_info_t *info)
{
	char **k;
	char *v;

	if (info->args[1] == NULL || info->args[2] == NULL)
	{
		pce(info, ": Incorrect number of args\n");
		info->exit_code = 2;
		return;
	}
	k = fck(info->env_vars, info->args[1]);
	if (k == NULL)
	{
		ack(info);
	}
	else
	{
		v = acv(info->args[1], info->args[2]);
		if (v == NULL)
		{
			pce(info, NULL);
			free(info->cmd_buf);
			free(info->cmd_list);
			free(info->args);
			dse(info->env_vars);
			exit(127);
		}
		free(*k);
		*k = v;
	}
	info->exit_code = 0;
}
/**
 * ssseu - removes env variable
 * @info: pointer to shell
 */
void ssseu(shell_info_t *info)
{
	char **k, **ne;
	unsigned int x, y;

	if (info->args[1] == NULL)
	{
		pce(info, ": Incorrect number of args\n");
		info->exit_code = 2;
		return;
	}
	k = fck(info->env_vars, info->args[1]);
	if (k == NULL)
	{
		pce(info, ": No variable unset");
		return;
	}
	for (x = 0; info->env_vars[x] != NULL; x++)
		;
	ne = malloc(sizeof(char *) * x);
	if (ne == NULL)
	{
		pce(info, NULL);
		info->exit_code = 127;
		ses(info);
	}
	for (x = 0; info->env_vars[x] != *k; x++)
		ne[x] = info->env_vars[x];
	for (y = x + 1; info->env_vars[y] != NULL; y++, x++)
		ne[x] = info->env_vars[y];
	ne[x] = NULL;
	free(*k);
	free(info->env_vars);
	info->env_vars = ne;
	info->exit_code = 0;
}
