#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, c, i, p;
    do // pedir somente numeros inteiros entre 1 e 8
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (i = 0; i < height; i++) // Loop Principal
    {
        for (c = 0; c < height; c++) // C = Coluna
        {
            if (c < height - i - 1) // Coluna < altura - loop principal - 1
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (p = 0; p < i + 1; p++) // P = Piramide
        {
            printf("#");
        }
        printf("\n");
    }
}