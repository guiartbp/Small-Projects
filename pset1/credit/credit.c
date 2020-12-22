#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Variáveis iniciais
    long long cardNumber, digits;
    int count = 0;

    // Solicitando número de cartão
    do
    {
        cardNumber = get_long_long("Number: ");
    }
    while (cardNumber < 1);

    // Número de digitos
    digits = cardNumber;
    while (digits > 0)
    {
        digits = digits / 10;
        count++;
    }

    // Luhn’s Algorithm
    int a[count];
    int i, lastNumber, j;
    long long number = cardNumber, lessNumber;

    // Coloca números de trás pra frente na Array
    for (i = 0; i < count; i++)
    {
        lastNumber = number % 10;
        lessNumber = number / 10;
        number = lessNumber;

        for (j = 0; j < 1; j++)
        {
            a[i] = lastNumber;
            // printf("a[%i]: %i\n", i, a[i]); // -- Teste Array

        }
    }

    // Soma
    int sb, mult, nB, nC, sum;
    int countB = 0, countC = 0, sumB = 0, sumC = 0;
    int b[countB], c[countC];

    for (sb = 0; sb < count; sb++)
    {
        if ((sb % 2) == 1)
        {
            mult = a[sb] * 2;
            switch (mult)
            {
                case 10:
                    mult = 1 + 0;
                    break;
                case 12:
                    mult = 1 + 2;
                    break;
                case 14:
                    mult = 1 + 4;
                    break;
                case 16:
                    mult = 1 + 6;
                    break;
                case 18:
                    mult = 1 + 8;
                    break;
            }
            // printf("a[%i] = %i \n", sb, a[sb]);  //-- Teste Multiplicação
            b[countB] = mult;
            // printf("B[%i]: %i\n",countB, b[countB]);

            nB = b[countB] + sumB;
            // printf("b[countB]: %i + sumB: %i\n",b[countB], sumB);
            sumB = nB;
            countB++;
            // printf("Sum B: %i\n", sumB);

        }
        else
        {
            c[countC] = a[sb];
            // printf("c[%i]: %i\n",countC, c[countC]); // -- Teste Array
            nC = c[countC] + sumC;
            // printf("c[countC]: %i + sumC: %i\n",c[countC], sumC);
            sumC = nC;
            countC++;
            // printf("Sum C: %i\n", sumC);

        }

    }
    sum = sumB + sumC;
    // printf("Sum: %i\n", sum);

    // Validação do cartão e Bandeira
    if (sum % 10 == 0)
    {
        if ((count == 13 || count == 16) && (a[count - 1] == 4))
        {
            printf("VISA\n");
        }
        else if ((count == 15) && (a[count - 1] == 3) && (a[count - 2] == 4 || a[count - 2] == 7))
        {
            printf("AMEX\n");
        }
        else if ((count == 16) && (a[count - 1] == 5) && (a[count - 2] == 1 || a[count - 2] == 2 || a[count - 2] == 3 || a[count - 2] == 4
                 || a[count - 2] == 5))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
