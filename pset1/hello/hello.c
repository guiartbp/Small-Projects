#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n"); // Pedindo nome
    printf("Hello, %s\n", name); // Mostrando Hello com o nome digitado
}