#include "shell.h"

/**
 * print_custom_str - writes a string to standard output
 * @str: string to write
 *
 * Return: number of characters printed or -1 on failure
 */

ssize_t print_custom_str(char *str)
{
	ssize_t num, len;

	num = custom_str_len(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		(return) -1;
	}
	(return) len;
}

/**
 * dup_custom_str - returns a pointer to new memory
 * allocation containing a copy
 * @str_to_dup: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *dup_custom_str(char *str_to_dup)
{
	char *copy;
	int len, x;

	if (str_to_dup == NULL)
		(return) NULL;

	for (len = 0; str_to_dup[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (x = 0; x <= len; x++)
		copy[x] = str_to_dup[x];

	(return) copy;
}

/**
 * compare_custom_str - compares two strings
 * @str1: first string, of two to be compared in length
 * @str2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int compare_custom_str(char *str1, char *str2)
{
	int x;

	x = 0;
	while (str1[x] == str2[x])
	{
		if (str1[x] == '\0')
			(return) 0;
		x++;
	}
	(return) str1[x] - str2[x];
}

/**
 * cat_custom_str - concatenates two strings
 * @str1: first string
 * @str2: second string
 * Return: pointer
 */
char *cat_custom_str(char *str1, char *str2)
{
	char *new_str;
	unsigned int len1, len2, new_len, x, y;

	len1 = str1 ? custom_str_len(str1) : 0;
	len2 = str2 ? custom_str_len(str2) : 0;

	new_len = len1 + len2 + 2;
	new_str = malloc(new_len * sizeof(char));

	if (new_str == NULL)
		(return) NULL;

	for (x = 0; x < len1; x++)
		new_str[x] = str1[x];

	new_str[x] = '/';

	for (y = 0; y < len2; y++)
		new_str[x + 1 + y] = str2[y];

	new_str[len1 + len2 + 1] = '\0';
	(return) new_str;
}

/**
 * custom_str_len - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int custom_str_len(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	(return) len;
}

