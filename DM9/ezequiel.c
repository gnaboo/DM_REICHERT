#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Iterator { int value; struct Iterator* next; };
struct HashNode { int key; int value; struct HashNode* next; };
struct HashTable { int size; struct HashNode** buckets; };

// Typedefs
typedef struct Iterator Iterator;
typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

// Utils
void print_array_int(int* array, int size)
{
    int start = size < 0 ? 1 : 0;
    if (size < 0) size = array[0];

    for (int i = start; i < size + start; i += 1) printf("%d ", array[i]);
    printf("\n");
}

void print_newline() // ocaml equivalent
{
    printf("\n");
}

// Iterator
Iterator* create_iterator(int value)
{
    Iterator* iterator = malloc(sizeof(Iterator));

    iterator->value = value;
    iterator->next = NULL; // null pointer at the end

    return iterator;
}

void add_iterator(Iterator* iterator, int value)
{
    Iterator* new_iterator = create_iterator(value);

    while (iterator->next) iterator = iterator->next;
    iterator->next = new_iterator;
}

void free_iterator(Iterator* iterator)
{
    while (iterator)
    {
        Iterator* next = iterator->next;
        free(iterator);

        iterator = next;
    }
}

void print_iterator(Iterator* iterator)
{
    while (iterator)
    {
        printf("%d ", iterator->value);
        iterator = iterator->next;
    }

    printf("\n");
}

// HashTable
HashTable* create_htbl(int size)
{
    HashTable* table = malloc(sizeof(HashTable));

    table->buckets = malloc(size * sizeof(HashNode*));
    table->size = size;

    for (int i = 0; i < size; i += 1) table->buckets[i] = NULL;
    return table;
}

int hash_htbl(HashTable* table, int key)
{
    // this will be enough for the use we'll make of it... (same as a dict. in this case)
    return key % table->size;
}

void insert(HashTable* table, int key, int value)
{
    int index = hash_htbl(table, key);

    HashNode* node = table->buckets[index];
    HashNode* prev = NULL;

    while (node)
    {
        if (node->key == key) return;

        prev = node;
        node = node->next;
    }

    HashNode* new_node = malloc(sizeof(HashNode));

    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    if (prev) prev->next = new_node;
    else table->buckets[index] = new_node;
}

bool exists_htbl(HashTable* table, int key)
{
    int index = hash_htbl(table, key);
    HashNode* node = table->buckets[index];

    while (node)
    {
        if (node->key == key) return true;

        node = node->next;
    }

    return false;
}

void free_htbl(HashTable* table)
{
    for (int i = 0; i < table->size; i += 1)
    {
        HashNode* node = table->buckets[i];

        while (node)
        {
            HashNode* next = node->next;
            free(node);

            node = next;
        }
    }

    free(table->buckets);
    free(table);
}

// Code
// Exercice 80
int ppcm_ens(int* tab, int size)
{
    int ppcm = 1;

    for (int i = 0; i < size; i += 1)
    {
        int a = tab[i];
        int b = ppcm;

        if (a <= 0)
        {
            printf("Error: %d is not a positive integer\n", a);
            exit(1);
        }

        while (b != 0)
        {
            int r = a % b;
            a = b;
            b = r;
        }

        ppcm *= tab[i] / a;
    }

    return ppcm;
}

// Exercice 81
bool subsetsum(int* tab, int size, int sum)
{
    // Other option, use the hashtable to store the already computed sums
    // and check if the sum is in the hashtable
    int sums_count = 1 << size; // 2^size
    HashTable* sums = create_htbl(sums_count);

    // Iterate over all subsets
    // If the sum is already in the hashtable, return true
    // Otherwise, add the sum to the hashtable
    for (int i = 0; i < sums_count; i += 1)
    {
        int subset_sum = 0;
        int pow2 = 1;

        for (int j = 0; j < size; j += 1)
        {
            if ((i / pow2) % 2 == 1)
                subset_sum += tab[j];
            pow2 *= 2;
        }

        if (subset_sum == sum)
        {
            free_htbl(sums);
            return true;
        }

        insert(sums, subset_sum, 1);
    }

    // check if the sum is in the HashTable (last check)
    bool found = exists_htbl(sums, sum);

    free_htbl(sums);
    return found;
}

// Test
int main()
{
    // Exercice 80
    int tab80_1[] = { 2, 3, 4, 5, 6 };
    int tab80_2[] = { 1 };
    int tab80_3[] = { 1, 1 };
    int tab80_4[] = { 20, 42, 55, 27, 69, 55, 17, 64 };
    int tab80_5[] = { 2, 3, 7 };

    printf("Exercice 80 : %d\n", ppcm_ens(tab80_1, 5));
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_2, 1));
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_3, 2));
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_4, 8));
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_5, 3));

    print_newline();

    // Exercice 81
    int tab81_1[] = { 1, 2, 3, 4, 5 };
    int tab81_2[] = { 1, 2, 3, 4, 5, 6 };
    int tab81_3[] = { 1, 7, 6, 4 };
    int tab81_4[] = { 1, 1 };
    int tab81_5[] = { 0 };

    printf("Exercice 81 : %s\n", subsetsum(tab81_1, 5, 6) ? "true" : "false");
    printf("Exercice 81 : %s\n", subsetsum(tab81_2, 6, 10) ? "true" : "false");
    printf("Exercice 81 : %s\n", subsetsum(tab81_3, 4, 40) ? "true" : "false");
    printf("Exercice 81 : %s\n", subsetsum(tab81_4, 2, 1) ? "true" : "false");
    printf("Exercice 81 : %s\n", subsetsum(tab81_5, 1, 5) ? "true" : "false");

    print_newline();

    // Exercice 82
    // ..

    return 0;
}
