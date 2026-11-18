#include "function_pointers.h"

/**
 * array_iterator - executes a function on each array element
 * @array: array to iterate
 * @size: array size
 * @action: function to execute
 * Return: Nothing.
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t i;

	for (i = 0; i < size; i++)
	{
		action(array[i]);
	}
}
