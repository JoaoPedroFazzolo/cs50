#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value = (hash_value << 2) ^ word[i];
    }

    return hash_value % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase for case-insensitive comparison
    char lowerWord[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++)
    {
        lowerWord[i] = tolower(word[i]);
    }
    lowerWord[strlen(word)] = '\0';

    // Hash the lowercase word to get the index
    unsigned int index = hash(lowerWord);

    // Traverse the linked list at the given index
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Compare the lowercase word with the current node's word
        if (strcmp(cursor->word, lowerWord) == 0)
        {
            // Word found in the dictionary
            return true;
        }
    }

    // Word not found in the dictionary
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        // Handle file opening failure
        return false;
    }

    // Initialize table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer for reading words from the dictionary
    char buffer[LENGTH + 1];

    // Read words from the dictionary
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            // Handle memory allocation failure
            fclose(file);
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, buffer);

        // Hash the word to get the index
        unsigned int index = hash(new_node->word);

        // Insert the new node at the beginning of the linked list
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close the dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Iterate through each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Traverse the linked list at the current index
        for (node *cursor = table[i]; cursor != NULL; cursor = cursor->next)
        {
            // Increment the word count
            count++;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Traverse the linked list at the current index
        while (table[i] != NULL)
        {
            // Keep a reference to the current node
            node *cursor = table[i];

            // Move to the next node
            table[i] = cursor->next;

            // Free the current node
            free(cursor);
        }
    }

    // Successfully unloaded the dictionary
    return true;
}
