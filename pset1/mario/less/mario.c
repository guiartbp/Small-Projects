#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); // Aqui impede numeros negativos, 0, acima de 9 e letras

    for (int i = 0; i < height; i++)
    {
        for (int p = 0; p < height - i - 1; p++) // O tanto número de pontos rodará enquanto for menor que a altura - (i - 1)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++) // Já os hashes rodará enquanto for menor que (i + 1)
        {
            printf("#");
        }

        printf("\n");
    }
}