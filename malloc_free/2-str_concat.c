#include "main.h"
#include <stdlib.h>

/**
 * str_concat - Joins two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: New string or NULL
 */
char *str_concat(char *s1, char *s2)
{
	char *str;
	int i = 0;
	int j = 0;
	int len1 = 0;
	int len2 = 0;

	if (s1 != NULL)
		while (s1[len1] != '\0')
			len1++;

	if (s2 != NULL)
		while (s2[len2] != '\0')
			len2++;

	str = malloc(len1 + len2 + 1);
	if (str == NULL)
		return (NULL);

	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}

	while (j < len2)
	{
		str[i] = s2[j];
		i++;
		j++;
	}

	str[i] = '\0';

	return (str);
}
