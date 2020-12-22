// Implements a dictionary's functionality

#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
int count = 0;


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int ht = hash(word);


    if (table[ht] == NULL)
    {
        return false;
    }

    node *cursor = table[ht];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // counter
    int hash = 0;
    // transform in lowercase for nothing diff in FOO, Foo, fOO,etc.
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        hash += tolower(word[i]);
    }
    // Brian mandou a dica, eu aceitei %N ksksks
    return (hash % N);
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read words
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocation of memory for new words
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            free(new_word);
            unload();
            return false;
        }

        // copy of words for node
        strcpy(new_word->word, word);
        new_word->next = NULL;

        //Function hash
        int ht = hash(word);
        // Create head

        if (table[ht] == NULL)
        {
            table[ht] = new_word;
        }
        else
        {
            new_word->next = table[ht];
            table[ht] = new_word;
        }
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}

