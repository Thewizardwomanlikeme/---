// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 17575;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i = hash(word);
    node *cursor = table[i];
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
    unsigned int hash_value = 0;
    for (int i = strlen(word) - 1, j = 0; j < 3 && word[j] != '\0'; i--, j++)
    {
        if (isalpha(word[j]))
        {
            int power = 1;
            int base = toupper(word[j]) - 'A';
            for (int n = 0; n < i; n++)
                power *= 26;
            hash_value += base * power;
        }
        else
            hash_value += 26;
    }
    return hash_value % N;
}

unsigned int word_count = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *text = fopen(dictionary, "r");
    if (text == NULL)
    {
        printf("Could not open file\n");
        return false;
    }

    // Initialize hash table once
    for (int k = 0; k < N; k++)
    {
        table[k] = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(text, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(text);
            return false;
        }

        strcpy(n->word, word);
        int i = hash(word);
        n->next = table[i];
        table[i] = n;
        word_count++; // increment here for every word
    }

    fclose(text);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
