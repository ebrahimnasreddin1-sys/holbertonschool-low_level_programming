#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int number = 0;

	while (number <= 15)
	{
		if (number < 10)
			putchar(number + '0');
		else
			putchar(number - 10 + 'a');
		number++;
	}
	putchar('\n');
	return (0);
}
