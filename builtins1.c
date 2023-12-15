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

    for (i = 0; sb[i].bf != NULL; i++)
    {
        if (ccs(info->args[0], sb[i].bn) == 0)
            break;
    }

    if (sb[i].bf != NULL)
        sb[i].bf(info);

    return sb[i].bf;
}

/**
 * ses - exits shell
 * @info: shell info
 */
void ses(shell_info_t *info)
{
    int s;

    if (ccs(info->args[0], "exit") == 0 && info->args[1] != NULL)
    {
        s = cstoi(info->args[1]);
        if (s == -1)
        {
            info->ec = 2;
            pce(info, ": Illegal number: ");
            pcm(info->args[1]);
            pcm("\n");
            free(info->cl);
            info->cl = NULL;
            return;
        }
        info->ec = s;
    }

    free(info->cb);
    free(info->args);
    free(info->cl);
    dse(info->ev);
    ex(info->ec);
}

/**
 * ssse - print shell environment
 * @info: shell info
 */
void ssse(shell_info_t *info)
{
    for (unsigned int i = 0; info->ev[i] != NULL; i++)
    {
        pcs(info->ev[i]);
        pcs("\n");
    }

    info->ec = 0;
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
        info->ec = 2;
        return;
    }

    k = fck(info->ev, info->args[1]);

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
            free(info->cb);
            free(info->cl);
            free(info->args);
            dse(info->ev);
            ex(127);
        }

        free(*k);
        *k = v;
    }

    info->ec = 0;
}

/**
 * ssseu - removes env variable
 * @info: pointer to shell
 */
void ssseu(shell_info_t *info)
{
    char **k, **ne;

    if (info->args[1] == NULL)
    {
        pce(info, ": Incorrect number of args\n");
        info->ec = 2;
        return;
    }

    k = fck(info->ev, info->args[1]);

    if (k == NULL)
    {
        pce(info, ": No variable unset");
        return;
    }

    unsigned int x, y;

    for (x = 0; info->ev[x] != NULL; x++)
        ;

    ne = malloc(sizeof(char *) * x);

    if (ne == NULL)
    {
        pce(info, NULL);
        info->ec = 127;
        ses(info);
    }

    for (x = 0; info->ev[x] != *k; x++)
        ne[x] = info->ev[x];

    for (y = x + 1; info->ev[y] != NULL; y++, x++)
        ne[x] = info->ev[y];

    ne[x] = NULL;

    free(*k);
    free(info->ev);
    info->ev = ne;
    info->ec = 0;
}
