#include "main.h"
#include <stdlib.h>
#include <limits.h>

/**
 * array_range - Creates an array of integers
 * @min: First number
 * @max: Last number
 *
 * Return: Array or NULL
 */
int *array_range(int min, int max)
{
	int *array;
	unsigned int size;
	unsigned int i;

	if (min > max)
		return (NULL);

	size = (unsigned int)max - (unsigned int)min + 1;

	if (size == 0 || size > (unsigned int)-1 / sizeof(int))
		return (NULL);

	array = malloc(sizeof(int) * size);

	if (array == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		array[i] = (int)((unsigned int)min + i);

	return (array);
}
