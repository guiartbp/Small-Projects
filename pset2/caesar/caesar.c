#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
// Abrir o arquivo com Comando em Linha
    // Comando em linha deve ter argc = 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }
    else
    {
        // Verifica se possui alguma letra no segundo argumento
        for (int s = 0; s < strlen(argv[1]); s++)
        {
            if (!isdigit(argv[1][s]))
            {
                printf("Usage: ./caesar key\n");
                exit(1);
            }

        }
    }
    // Transformar argv[1] em inteiro
    int k = atoi(argv[1]);

// Programa aberto
    // Variáveis iniciais
    string text;
    int i, Cup, Clw;

    // Pega o texto
    text = get_string("plaintext: ");

    // Criptografa e imprime
    printf("ciphertext: ");

    for (i = 0; i < strlen(text); i++)
    {
        Cup = (((text[i] - 65) + k) % 26) + 65; // C for UPpercase
        Clw = (((text[i] - 97) + k) % 26) + 97; // C for LoWercase
        if (isalpha(text[i]) && isupper(text[i]))
        {
            printf("%c", Cup); // print da letra criptografada
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            printf("%c", Clw); // print da letra criptografada
        }
        else
        {
            printf("%c", text[i]); // print se não for letra
        }
    }
    printf("\n");
}