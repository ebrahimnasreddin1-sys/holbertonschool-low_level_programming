#include <stdio.h>

/**
 * calcolator
 *
 */

int main(void)
{
	int number;

	printf("Simple Calculator\n");
	printf("1) Add\n");
	printf("2) Subtract\n");
	printf("3) Multiply\n");
	printf("4) Divide\n");
	printf("0) Quit\n");
	printf("Choice: ");

	number = 1;

	while (number != 0)
	{
		scanf("%d", &number);

		if (number == 0)
		{
			printf("Bye!\n");
			break;
		}
				if (number < 0 || number > 4)
				{
    				printf("Invalid choice\n");
				}
			
		
		
		printf("Choice: ");
	}

	return (0);
}
