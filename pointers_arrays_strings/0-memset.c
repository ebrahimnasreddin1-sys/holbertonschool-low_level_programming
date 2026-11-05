#include "main.h"

/**
 * _memset - Fills memory with a byte
 * @s: Memory area
 * @b: Byte to fill
 * @n: Number of bytes
 *
 * Return: s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}
