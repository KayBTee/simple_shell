#include "shell.h"

/**
 * rcp - Reallocates a pointer to double the space
 * @p: Pointer to the old array
 * @s: Pointer to number of elements in the old array
 *
 * Return: Pointer to the new array
 */
char **rcp(char **p, size_t *s)
{
	char **np;
	size_t x;

	np = malloc(sizeof(char *) * ((*s) + 10));

	if (np == NULL)
	{
		free(p);
		return (NULL);
	}

	for (x = 0; x < (*s); x++)
	{
		np[x] = p[x];
	}

	*s += 10;
	free(p);

	return (np);
}
