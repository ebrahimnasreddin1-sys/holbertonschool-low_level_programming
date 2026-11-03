#include "main.h"
#include <limits.h>

/**
 * _atoi - Converts a string to an integer
 * @s: The string
 *
 * Return: The number
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int num = 0;
	int digit;
	int limit;

	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
	}

	if (sign == -1)
		limit = INT_MIN;
	else
		limit = -INT_MAX;

	while (s[i] >= '0' && s[i] <= '9')
	{
		digit = s[i] - '0';

		if (num < limit / 10 ||
		    (num == limit / 10 && digit > -(limit % 10)))
		{
			if (sign == -1)
				return (INT_MIN);
			return (INT_MAX);
		}

		num = num * 10 - digit;
		i++;
	}

	if (sign == -1)
		return (num);

	return (-num);
}
