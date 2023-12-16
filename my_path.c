#include "shell.h"
/**
 * fep - Gets PATH variables
 * @ev: Array of environment vars
 *
 * Return: Pointer to node containing PATH
 */
char *fep(char **ev)
{
	char *p = "PATH=";
	unsigned int x, y;

	for (x = 0; ev[x] != NULL; x++)
	{
		for (y = 0; p[y] != '\0'; y++)
		{
			if (p[y] != ev[x][y])
				break;
		}
		if (p[y] == '\0')
			break;
	}
	return (ev[x]);
}
/**
 * esc - Executes command in the path
 * @cmd: Full path to command
 * @info: Pointer to struct
 *
 * Return: 0
 */
int esc(char *cmd, shell_info_t *info)
{
	pid_t cp;

	if (access(cmd, X_OK) == 0)
	{
		cp = fork();
		if (cp == -1)
			pce(info, NULL);
		if (cp == 0)
		{
			if (execve(cmd, info->args, info->env_vars) == -1)
				pce(info, NULL);
		}
		else
		{
			wait(&info->exit_code);
			if (WIFEXITED(info->exit_code))
				info->exit_code = WEXITSTATUS(info->exit_code);
			else if (WIFSIGNALED(info->exit_code) && WTERMSIG
					(info->exit_code) == SIGINT)
				info->exit_code = 130;
			return (0);
		}
		info->exit_code = 127;
		return (1);
	}
	else
	{
		pce(info, ": permission denied\n");
		info->exit_code = 126;
	}
	return (0);
}
/**
 * cep - Checks if cmd is in PATH
 * @info: Pointer to struct of shell information
 *
 * Return: void
 */
void cep(shell_info_t *info)
{
	char *p, *pd = NULL, *c = NULL;
	unsigned int x = 0, n = 0;
	char **pt;
	struct stat buf;

	if (cde(info->args[0]))
		n = ecd(info);
	else
	{
		p = fep(info->env_vars);
		if (p != NULL)
		{
			pd = dup_custom_str(p + 5);
			pt = tokenize_command(pd, ":");
			for (x = 0; pt && pt[x]; x++, free(c))
			{
				c = cat_custom_str(pt[x], info->args[0]);
				if (stat(c, &buf) == 0)
				{
					n = esc(c, info);
					free(c);
					break;
				}
			}
			free(pd);
			if (pt == NULL)
			{
				info->exit_code = 127;
				ses(info);
			}
		}
		if (p == NULL || pt[x] == NULL)
		{
			pce(info, ": not found\n");
			info->exit_code = 127;
		}
		free(pt);
	}
	if (n == 1)
		ses(info);
}
/**
 * ecd - Executes cmd in current directory
 * @info: Points of shell
 *
 * Return: 0 success
 */
int ecd(shell_info_t *info)
{
	pid_t cp;
	struct stat buf;

	if (stat(info->args[0], &buf) == 0)
	{
		if (access(info->args[0], X_OK) == 0)
		{
			cp = fork();
			if (cp == -1)
				pce(info, NULL);
			if (cp == 0)
			{
				if (execve(info->args[0], info->args, info->env_vars) == -1)
					pce(info, NULL);
			}
			else
			{
				wait(&info->exit_code);
				if (WIFEXITED(info->exit_code))
					info->exit_code = WEXITSTATUS(info->exit_code);
				else if (WIFSIGNALED(info->exit_code) && WTERMSIG
						(info->exit_code) == SIGINT)
					info->exit_code = 130;
				return (0);
			}
			info->exit_code = 127;
			return (1);
		}
		else
		{
			pce(info, ": permission denied\n");
			info->exit_code = 126;
		}
		return (0);
	}
	pce(info, ": not found\n");
	info->exit_code = 127;
	return (0);
}
/**
 * cde - Checks if cmd is part of path
 * @p: cmd
 *
 * Return: 1 successful
 */
int cde(char *p)
{
	unsigned int x;

	x = 0;

	while (p[x])
	{
		if (p[x] == '/')
		{
			return (1);
		}
		x++;
	}
	return (0);
}
