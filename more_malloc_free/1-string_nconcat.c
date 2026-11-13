#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - Joins two strings
 * @s1: First string
 * @s2: Second string
 * @n: Number of bytes
 *
 * Return: New string or NULL
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *str;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int len1 = 0;
	unsigned int len2 = 0;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0' && len2 < n)
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
