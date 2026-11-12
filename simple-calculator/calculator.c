#include <stdio.h>

/**
 * main - Simple Calculator
 *
 * Return: 0
 */

int main(void)
{
    int number;
    int a;
    int b;

    printf("Simple Calculator\n");
    printf("1) Add\n");
    printf("2) Subtract\n");
    printf("3) Multiply\n");
    printf("4) Divide\n");
    printf("0) Quit\n");

    number = 1;

    while (number != 0)
    {
        printf("Choice: ");
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

        if (number == 1)
        {
            printf("A: ");
            scanf("%d", &a);

            printf("B: ");
            scanf("%d", &b);

            printf("Result: %d\n", a + b);
        }
    }

    return (0);
}
