#include "shell.h"

/**
 * pce - Prints error messages to standard error
 * @info: Pointer to shell info structure
 * @msg: Message to print
 *
 * Return: void
 */
void pce(shell_info_t *info, char *msg)
{
	char *count;

	print_custom_str(info->init_args[0]);
	print_custom_str(": ");
	count = itcs(info->cmd_count);
	print_custom_str(": ");
	print_custom_str(info->args[0]);

	if (msg)
		print_custom_str(msg);
	else
		perror("");

	free(count);
}

/**
 * pecm - Prints a string to standard error
 * @str: String to print
 *
 * Return: void
 */
void pecm(char *str)
{
	ssize_t n, len;

	n = custom_str_len(str);
	len = write(STDERR_FILENO, str, n);

	if (len != n)
	{
		perror("Fatal Error");
		exit(1);
	}
}

/**
 * itcs - Converts an unsigned int to a string
 * @v: Unsigned int to convert
 *
 * Return: Pointer to the converted string
 */
char *itcs(unsigned int v)
{
	char *ns;
	unsigned int t, d;

	t = v;

	for (d = 0; t != 0; d++)
		t /= 10;

	ns = malloc(sizeof(char) * (d + 1));

	if (ns == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}

	ns[d] = '\0';

	for (--d; v; --d)
	{
		ns[d] = (v % 10) + '0';
		v /= 10;
	}

	return (ns);
}
