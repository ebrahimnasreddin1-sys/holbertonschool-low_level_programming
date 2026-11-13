#include "main.h"
#include <stdlib.h>

/**
 * create_array - Creates an array
 * @size: Array size
 * @c: Character
 *
 * Return: Array or NULL
 */
char *create_array(unsigned int size, char c)
{
	char *array;
	unsigned int i;

	if (size == 0)
		return (NULL);

	array = malloc(size);

	if (array == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		array[i] = c;
	}

	return (array);
}
