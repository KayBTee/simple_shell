#include "shell.h"
/**
 * check_match - checks if a char matches any in a string
 * @c: character to be checked
 * @str: string to check
 *
 *
 * Return: 1 else 0
 */
unsigned int check_match(char c, const char *str)
{
    unsigned int x;

    x = 0;

    while (str[x] != '\0')
    {
        if (c == str[x])
            return 1;
        x++;
    }
    return 0;
}
/**
 * custom_strtok_r - custom strtok
 * @str:string to tokenize
 * @delim: delimeter
 *
 *
 * Return: pointer to next token
 */
char *custom_strtok_r(char *str, const char *delim)
{
    static char *tok_start;
    static char *save_ptr;
    unsigned int x;

    if (str != NULL)
        save_ptr = str;
    tok_start = save_ptr;
    
    if (tok_start == NULL)
        return NULL;

    for (x = 0; save_ptr[x] != '\0'; x++)
    {
        if (check_match(save_ptr[x], delim) == 0)
            break;
    }

    if (save_ptr[x] == '\0' || save_ptr[x] == '#')
    {
        save_ptr = NULL;
        return NULL;
    }

    tok_start = save_ptr + x;
    save_ptr = tok_start;

    for (x = 0; save_ptr[x] != '\0'; x++)
    {
        if (check_match(save_ptr[x], delim) == 1)
            break;
    }

    if (save_ptr[x] == '\0')
        save_ptr = NULL;
    else
    {
        save_ptr[x] = '\0';
        save_ptr = save_ptr + x + 1;

        if (*save_ptr == '\0')
            save_ptr = NULL;
    }

    return tok_start;
}
