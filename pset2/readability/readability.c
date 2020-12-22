#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Funções
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// Variáveis

float W = 1, letters, sentences, CLI, L, S;

int main(void)
{
    // Input Text
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) < 1);

    // Letters
    letters = count_letters(text);
    // printf("Letters: %f\n", letters);

    // Words
    W = count_words(text);
    // printf("Words: %f\n", W);

    // Sentences
    sentences = count_sentences(text);
    // printf("Sentences: %f\n", sentences);


    // Index Coleman-Liau
    L = letters / W * 100;
    S = sentences / W * 100;
    CLI = (0.0588 * L) - (0.296 * S) - 15.8;
    CLI = round(CLI);
    // printf("%f\n", CLI);
    if (CLI <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (CLI >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) CLI);
    }
}

// Count Letters
int count_letters(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Count Words
int count_words(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            W++;
        }
    }
    return W;
}

// Count Sentences
int count_sentences(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}