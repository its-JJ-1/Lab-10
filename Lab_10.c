#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TrieNode structure
typedef struct TrieNode
{
    struct TrieNode *children[26];
    int count; // To store the count of occurrences
} TrieNode;

// Initializes a trie node
struct TrieNode *createTrie()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node)
    {
        for (int i = 0; i < 26; i++)
        {
            node->children[i] = NULL;
        }
        node->count = 0;
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct TrieNode *root, char *word)
{
    TrieNode *node = root;
    int index;
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = word[i] - 'a';
        if (!node->children[index])
        {
            node->children[index] = createTrie();
        }
        node = node->children[index];
    }
    node->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct TrieNode *root, char *word)
{
    TrieNode *node = root;
    int index;
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = word[i] - 'a';
        if (!node->children[index])
        {
            return 0; // Word not found
        }
        node = node->children[index];
    }
    return node->count;
}

// Deallocate the trie structure
struct TrieNode *deallocateTrie(struct TrieNode *root)
{
    if (!root)
        return NULL;

    for (int i = 0; i < 26; i++)
    {
        if (root->children[i])
        {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
    return NULL;
}

// Reads the dictionary file and initializes the trie
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    int numWords = 0;
    char word[50];

    // Skip reading the first number
    fscanf(file, "%s", word);

    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = (char *)malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);

    // Print the input words
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }
    printf("\n");

    // Initialize the root of the trie
    TrieNode *root = createTrie();

    // Insert each word from the dictionary into the trie
    for (int i = 0; i < numWords; ++i)
    {
        insert(root, inWords[i]);
    }

    // Test cases
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    printf("output:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(root, pWords[i]));
    }
    printf("\n");

    // Deallocate the trie
    deallocateTrie(root);

    // Free allocated memory for inWords
    for (int i = 0; i < numWords; ++i)
    {
        free(inWords[i]);
    }

    return 0;
}
