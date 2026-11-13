
#include "dog.h"
#include <stdlib.h>

/**
 * copy_string - Copies a string
 * @str: The string
 *
 * Return: Copy or NULL
 */
static char *copy_string(char *str)
{
	char *copy;
	int i = 0;
	int len = 0;

	while (str[len] != '\0')
		len++;

	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);

	while (i <= len)
	{
		copy[i] = str[i];
		i++;
	}

	return (copy);
}

/**
 * new_dog - Creates a new dog
 * @name: Dog name
 * @age: Dog age
 * @owner: Dog owner
 *
 * Return: Dog or NULL
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;

	if (name == NULL || owner == NULL)
		return (NULL);

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	dog->name = copy_string(name);
	if (dog->name == NULL)
	{
		free(dog);
		return (NULL);
	}

	dog->owner = copy_string(owner);
	if (dog->owner == NULL)
	{
		free(dog->name);
		free(dog);
		return (NULL);
	}

	dog->age = age;

	return (dog);
}
