#include "main.h"
#include <stdlib.h>

/**
 * _strdup - Copies a string
 * @str: The string
 *
 * Return: New string or NULL
 */
char *_strdup(char *str)
{
	char *copy;
	int i = 0;
	int len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	copy = malloc(sizeof(char) * (len + 1));

	if (copy == NULL)
		return (NULL);

	while (i <= len)
	{
		copy[i] = str[i];
		i++;
	}

	return (copy);
}
