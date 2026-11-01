#include "main.h"

/**
 * print_line - Prints a line
 * @n: Number of underscores
 */
void print_line(int n)
{
	int i = 0;

	while (i < n)
	{
		_putchar('_');
		i++;
	}
	_putchar('\n');
}
