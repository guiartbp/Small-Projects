#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change owed: "); // Aqui pede o tanto necessário para trocar
    }
    while (dollars < 0);

    int cents = round(dollars * 100);

    int change = 0;
    int coin = 0;
    int coins[] = {25, 10, 5, 1};

    while (cents > change)
    {
        if (change + coins[0] <= cents) // Se o troco + 25 centavos for menor ou igual que os centavos (devidos)
        {
            change = change + coins[0];
            coin++;
        }
        else if (change + coins[1] <= cents) // Se o troco + 10 centavos for menor ou igual que os centavos (devidos)
        {
            change = change + coins[1];
            coin++;
        }
        else if (change + coins[2] <= cents) // Se o troco + 5 centavos for menor ou igual que os centavos (devidos)
        {
            change = change + coins[2];
            coin++;
        }
        else
        {
            change = change + coins[3]; // Se o troco + 1 centavo for menor ou igual que os centavos (devidos)
            coin++;
        }
        // change = change + coin[x] == o troco que tenho (0) + a moeda (25, 10, 5, 1) até dar os centavos devidos
    }

    printf("%i\n", coin);

}