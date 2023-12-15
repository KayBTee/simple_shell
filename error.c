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

    pcs(info->init_args[0]);
    pcs(": ");
    count = itcs(info->cmd_count);
    pcs(": ");
    pcs(info->args[0]);

    if (msg)
        pcs(msg);
    else
        pe("");

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

    n = csl(str);
    len = write(STDERR_FILENO, str, n);

    if (len != n)
    {
        pe("Fatal Error");
        ex(1);
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
        pe("Fatal Error1");
        ex(127);
    }

    ns[d] = '\0';

    for (--d; v; --d)
    {
        ns[d] = (v % 10) + '0';
        v /= 10;
    }

    return ns;
}
