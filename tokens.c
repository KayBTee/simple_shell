#include "shell.h"

/**
 * tokenize_command - tokenizes a command buffer with a delimeter
 * @cmd_buffer: command buffer to tokenize
 * @delimeter: delimeter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **tokenize_command(char *cmd_buffer, char *delimeter)
{
	char **tokens = NULL;
	size_t x = 0, mcount = 10;

	if (cmd_buffer == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * mcount);

	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}

	while ((tokens[x] = cstrtok_r(cmd_buffer, delimeter)) != NULL)
	{
		x++;
		if (x == mcount)
		{
			tokens = rcp(tokens, &mcount);

			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		cmd_buffer = NULL;
	}

	return (tokens);
}
