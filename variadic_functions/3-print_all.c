#include <stdio.h>
#include <stdarg.h>
#include "variadic_functions.h"

/**
 * print_separator - prints separator
 * @count: number of arguments printed
 */
void print_separator(int count)
{
	if (count > 0)
		printf(", ");
}

/**
 * print_string - prints a string
 * @str: string to print
 */
void print_string(char *str)
{
	if (str == NULL)
	{
		printf("(nil)");
		return;
	}
	printf("%s", str);
}

/**
 * print_all - prints anything
 * @format: list of types of arguments
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i;
	int count;
	char *str;

	i = 0;
	count = 0;
	va_start(args, format);

	while (format != NULL && format[i] != '\0')
	{
		switch (format[i])
		{
		case 'c':
			print_separator(count);
			printf("%c", va_arg(args, int));
			count++;
			break;
		case 'i':
			print_separator(count);
			printf("%d", va_arg(args, int));
			count++;
			break;
		case 'f':
			print_separator(count);
			printf("%f", va_arg(args, double));
			count++;
			break;
		case 's':
			print_separator(count);
			str = va_arg(args, char *);
			print_string(str);
			count++;
			break;
		}
		i++;
	}

	va_end(args);
	printf("\n");
}
