#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string texto;
// Funções para validar key
bool key_length(string text[]);
bool non_alphabetic(string text[]);
bool repeat_chars(string text[]);

// Função Criptografar
string cript(string texto, string argv[]);

int main(int argc, string argv[])
{
// Validando Key
// Não pode ter mais ou menos de 2 comando de argumentos
    if (argc != 2)
    {
        printf("Usage: ./substitution key ARGC\n");
        exit(1);
    }

// O tamanho do argumento 2 tem que ser de 26
    else if (key_length(argv) == 1)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }
// O argumento 2 não pode ter char não alfabético e nem repetido
    else if (non_alphabetic(argv) == 1 || repeat_chars(argv) == 1)
    {
        printf("Usage: ./substitution key non_alphabetic\n");
        exit(1);
    }

// Plaintext
    else
    {
        texto = get_string("plaintext: ");
    }

// Criptografar

    printf("ciphertext: ");
    cript(texto, argv);

}

// Validando Key

// Tamanho do argumento
bool key_length(string text[])
{
    if (strlen(text[1]) != 26)
    {
        return 1;
    }
    return 0;
}

// Verifica se o argumento tem apenas letras
bool non_alphabetic(string text[])
{
    for (int i = 0; i < strlen(text[1]); i++)
    {
        if (!isalpha(text[1][i]))
        {
            return 1;
        }
    }
    return 0;
}

// Verifica se o char não repete no argumento
bool repeat_chars(string text[])
{
    for (int i = 0; i < strlen(text[1]); i++)
    {
        text[1][i] = toupper(text[1][i]);

        for (int j = 0; j < i; j++)
        {
            if (text[1][j] == text[1][i])
            {
                return 1;
            }
        }
    }
    return 0;
}

// Criptografando

string cript(string text, string code[])
{
    char abc[strlen(code[1])];

    for (int i = 0; i < strlen(code[1]); i++)
    {
        abc[i] = code[1][i];
    }

    for (int j = 0; j < strlen(text); j++)
    {
        if (isalpha(text[j]) && isupper(text[j]))
        {
            int Cup = text[j] - 65;
            text[j] = abc[Cup];
            printf("%c", toupper(text[j]));
        }
        else if (isalpha(text[j]) && islower(text[j]))
        {
            int Clw = text[j] - 97;
            text[j] = abc[Clw];
            printf("%c", tolower(text[j]));
        }
        else
        {
            printf("%c", text[j]);
        }
    }
    printf("\n");
    return 0;
}
