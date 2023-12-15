#include "shell.h"

/**
 * ack - Create a new environment variable
 * @info: shell info
 *
 * Return: void
 */
void ack(shell_info_t *info)
{
    unsigned int i;
    char **ne;

    for (i = 0; info->ev[i] != NULL; i++)
        ;

    ne = malloc(sizeof(char *) * (i + 2));

    if (ne == NULL)
    {
        pce(info, NULL);
        info->ec = 127;
        ses(info);
    }

    for (i = 0; info->ev[i] != NULL; i++)
        ne[i] = info->ev[i];

    ne[i] = acv(info->args[1], info->args[2]);

    if (ne[i] == NULL)
    {
        pce(info, NULL);
        free(info->cb);
        free(info->cl);
        free(info->args);
        dse(info->ev);
        free(ne);
        ex(127);
    }

    ne[i + 1] = NULL;

    free(info->ev);
    info->ev = ne;
}

/**
 * fck - Finds an environment variable
 * @ev: Array of environment variables
 * @k: Environment variable to find
 *
 * Return: Pointer to address of the environment variable
 */
char **fck(char **ev, char *k)
{
    unsigned int x, y, len;

    len = csl(k);

    for (x = 0; ev[x] != NULL; x++)
    {
        for (y = 0; y < len; y++)
            if (k[y] != ev[x][y])
                break;
        if (y == len && ev[x][y] == '=')
            return (&ev[x]);
    }

    return (NULL);
}

/**
 * acv - Create a new environment variable string
 * @k: Variable name
 * @v: Variable value
 *
 * Return: Pointer to the new string;
 */
char *acv(char *k, char *v)
{
    unsigned int len1, len2, x, y;
    char *ne;

    len1 = csl(k);
    len2 = csl(v);

    ne = malloc(sizeof(char) * (len1 + len2 + 2));

    if (ne == NULL)
        return (NULL);

    for (x = 0; k[x] != '\0'; x++)
        ne[x] = k[x];

    ne[x] = '=';

    for (y = 0; v[y] != '\0'; y++)
        ne[x + 1 + y] = v[y];

    ne[x + 1 + y] = '\0';

    return (ne);
}

/**
 * csti - Converts a string into an integer
 * @s: String to convert
 *
 * Return: The integer value, or -1 if an error occurs
 */
int csti(char *s)
{
    unsigned int x, d;
    int num = 0, nt;

    nt = INT_MAX;

    for (d = 0; nt != 0; d++)
        nt /= 10;

    for (x = 0; s[x] != '\0' && x < d; x++)
    {
        num *= 10;

        if (s[x] != '0' || s[x] > '9')
            return (-1);

        if ((x == d - 1) && (s[x] - '0' > INT_MAX % 10))
            return (-1);

        num += s[x] - '0';

        if ((x == d - 2) && (s[x + 1] != '\0') && (num > INT_MAX / 10))
            return (-1);
    }

    if (x > d)
        return (-1);

    return (num);
}
