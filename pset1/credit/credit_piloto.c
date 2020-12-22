#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char numbers[15];
    long long number, last, n, number_for = 0; // Pegar número
    int a[15], b[7], c[7];// Arrays
    int i, j, k, m, sb, sc; // For
    int mult, last_mult, n_mult; // Multipcação
    int sum = 0, sumb = 0, sumc = 0; // Soma
    int loopb = 0, loopc = 0;


    do // Pegar número do Cartão de Crédito
    {
        number = get_long("Number: ");
    }
    while (number < 1);
    // printf("%lli\n", number);

    number_for = number;
    for (i = 0; i < 16; i++) // Pegando os números
    {
        last = number_for % 10; // Pega  o último número
        n = number_for / 10; // Aqui tira o último número
        number_for = n;
        for (j = 0; j < 1; j++) // Manda o número para o Array (a)
        {
            a[i] = last;
            if ((i % 2) != 0)
            {
                mult = a[i] * 2;
                // printf("%i", mult);
                switch (mult) // Se  12 = 1 + 2
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
                for (k = 0; k < 1; k++)
                {
                    b[loopb] = mult;
                    // printf("b: %i\n", b[loopb]);
                }
                loopb++;
            }
            else
            {
                c[loopc] = last;
                // printf("c: %i\n", c[loopc]);
                loopc++;
            }
        }
    }
    for (sb = 0; sb < 8; sb++) // Soma Array
    {
        sumb = sumb + b[sb];
    }
    for (sc = 0; sc < 8; sc++) // Soma Array
    {
        sumc = sumc + c[sc];
    }
    sum = sumb + sumc;
    if ((sum % 10) == 0)
    {
        sprintf(numbers, "%lld", number);
        if (numbers[0] == '3' && (numbers[1] == '4' || numbers[1] == '7'))
        {
            printf("AMEX");
        }
        else if (numbers[0] == '5' && (numbers[1] == '1' || numbers[1] == '2' || numbers[1] == '3' || numbers[1] == '4' || numbers[1] == '5'))
        {
            printf("MASTERCARD");
        }
        else if (numbers[0] == '4')
        {
            printf("VISA");
        }
        else
        {
        printf("INVALID");
        }
    }
    else
    {
        printf("INVALID");
    }

    // printf("%i\n",sum);
    printf("\n");

}