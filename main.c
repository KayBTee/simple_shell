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
        pcs("\n$ ");
    else
        pcs("\n");
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
        pcs("$ ");

    while (getline(&(info.cmd_buffer), &bl, stdin) != -1)
    {
        info.cc++;
        info.cl = tc(info.cmd_buffer, ";");

        for (i = 0; info.cl && info.cl[i] != NULL; i++)
        {
            info.args = tc(info.cl[i], "\n \t\r");

            if (info.args && info.args[0])
            {
                if (isb(&info) == NULL)
                    cep(&info);
            }

            free(info.args);
        }

        free(info.cmd_buffer);
        free(info.cl);

        if (ip == 0)
            pcs("$ ");

        info.cmd_buffer = NULL;
    }

    if (ip == 0)
        pcs("\n");

    dse(info.env_vars);
    free(info.cmd_buffer);
    ex(info.ec);
}
