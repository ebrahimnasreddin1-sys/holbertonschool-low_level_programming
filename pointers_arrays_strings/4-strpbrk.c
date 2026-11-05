#include "main.h"

/**
 * _strpbrk - Finds the first matching character
 * @s: The string to search
 * @accept: Characters to find
 *
 * Return: Pointer to matching character or NULL
 */
char *_strpbrk(char *s, char *accept)
{
	int i = 0;
	int j;

	while (s[i] != '\0')
	{
		j = 0;

		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
			{
				return (s + i);
			}
			j++;
		}
		i++;
	}

	return (0);
}
