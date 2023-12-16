#include "shell.h"

/**
 * cse - creates shell environment
 * @ev: Environment passed to the main
 *
 * Return: pointer to new environment
 */
char **cse(char **ev)
{
	char **n = NULL;
	size_t x;

	for (x = 0; ev[x] != NULL; x++)
		;

	n = malloc(sizeof(char *) * (x + 1));

	if (n == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}

	for (x = 0; ev[x] != NULL; x++)
		n[x] = dup_custom_str(ev[x]);

	n[x] = NULL;

	return (n);
}

/**
 * dse - free shell
 * @ev: Shell environment
 */
void dse(char **ev)
{
	unsigned int x;

	x = 0;

	while (ev[x] != NULL)
	{
		free(ev[x]);
		x++;
	}

	free(ev);
}
