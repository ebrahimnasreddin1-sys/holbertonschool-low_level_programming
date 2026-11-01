#include "main.h"

/**
 * print_diagonal - Prints a diagonal line
 * @n: Number of lines
 */
void print_diagonal(int n)
{
	int i = 0;
	int j;

	while (i < n)
	{
		j = 0;
		while (j < i)
		{
			_putchar(' ');
			j++;
		}
		_putchar('\\');
		_putchar('\n');
		i++;
	}
	if (n <= 0)
		_putchar('\n');
}
