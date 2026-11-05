#include "main.h"

/**
 * cap_string - Capitalizes all words
 * @s: The string
 *
 * Return: s
 */
char *cap_string(char *s)
{
	int i = 0;
	int new_word = 1;

	while (s[i] != '\0')
	{
		if (new_word && s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] = s[i] - 32;
		}

		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
		    s[i] == ',' || s[i] == ';' || s[i] == '.' ||
		    s[i] == '!' || s[i] == '?' || s[i] == '"' ||
		    s[i] == '(' || s[i] == ')' || s[i] == '{' ||
		    s[i] == '}')
		{
			new_word = 1;
		}
		else
		{
			new_word = 0;
		}

		i++;
	}

	return (s);
}
