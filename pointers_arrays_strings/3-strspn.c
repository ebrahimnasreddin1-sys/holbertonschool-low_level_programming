#include "main.h"

/**
 * _strspn - Counts matching characters from the start
 * @s: The string
 * @accept: Accepted characters
 *
 * Return: Number of matching characters
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i = 0;
	int j;

	while (s[i] != '\0')
	{
		j = 0;

		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
			{
				break;
			}
			j++;
		}

		if (accept[j] == '\0')
		{
			break;
		}

		i++;
	}

	return (i);
}
