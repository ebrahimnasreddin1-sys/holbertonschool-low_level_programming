#include "main.h"

/**
 * _strstr - Finds a substring in a string
 * @haystack: The string to search
 * @needle: The substring to find
 *
 * Return: Pointer to substring or NULL
 */
char *_strstr(char *haystack, char *needle)
{
	int i = 0;
	int j;

	if (needle[0] == '\0')
	{
		return (haystack);
	}

	while (haystack[i] != '\0')
	{
		j = 0;

		while (needle[j] != '\0' &&
		       haystack[i + j] != '\0' &&
		       haystack[i + j] == needle[j])
		{
			j++;
		}

		if (needle[j] == '\0')
		{
			return (haystack + i);
		}

		i++;
	}

	return (0);
}
