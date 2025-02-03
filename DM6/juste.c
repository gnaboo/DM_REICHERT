/*#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Couple { int a; int b; };

struct Card { char* value; char* color; };

struct HashNode { int key; int count; struct HashNode* next; };
struct HashTable { int size; struct HashNode** buckets; };

// Typedefs
typedef struct Couple Couple;

typedef struct Card Card;

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

// Utils
void print_array_int(int* array, int size)
{
    for (int i = 0; i < size; i += 1) printf("%d ", array[i]);
    printf("\n");
}

void print_array_float(double* array, int size)
{
    for (int i = 0; i < size; i += 1) printf("%f ", array[i]);
    printf("\n");
}

HashTable* create_table(int size)
{
    HashTable* table = malloc(sizeof(HashTable));

    table->buckets = malloc(size * sizeof(HashNode*));
    table->size = size;

    for (int i = 0; i < size; i += 1) table->buckets[i] = NULL;
    return table;
}

int get_count(HashTable* table, int key)
{
    int index = key % table->size;
    HashNode* node = table->buckets[index];

    while (node)
    {
        if (node->key == key) return node->count;
        node = node->next;
    }

    return 0;
}

void insert_or_update_table(HashTable* table, int key, int value)
{
    int index = key % table->size;
    HashNode* node = table->buckets[index];

    while (node)
    {
        if (node->key == key)
        {
            node->count = value;
            return;
        }

        node = node->next;
    }

    HashNode* new_node = malloc(sizeof(HashNode));

    new_node->key = key;
    new_node->count = value;
    new_node->next = table->buckets[index];

    table->buckets[index] = new_node;
}

void free_table(HashTable* table)
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

// Exercice 50
Couple tables(int n)
{
    if (n < 6)
    {
        printf("Erreur, n doit être supérieur ou égal à 6\n");
        exit(1);
    }

    // Check for every b value from 0 to 3
    for (int b = 0; b <= 3; b += 1)
    {
        int t = n - 3 * b;
        if (t % 4 == 0) return (Couple) { a: t / 4, b };
    }

    // si impossible (normalement, n'a pas lieu d'arriver)
    return (Couple) { -1, -1 };
}

// Exercice 51
double q1(double* table, int size)
{
    if (!(size % 4 == 1)) // en soit, le premier quartile d'un singleton est lui-même
    {
        printf("Erreur, la taille du tableau doit être de la forme 4k + 1");
        exit(1);
    }

    // return the fist quartile
    int n = (size - 1) / 4;
    return table[n];
}

// Exercice 53
int premiercommepremier(int* table, int size)
{
    for (int i = 1; i < size; i += 1)
        if (table[i] == table[0]) return i;

    return -1;
}

// Exercice 54
int* premiercommeavant(int* table, int size)
{
    // Init answer table
    int* t = malloc(2 * sizeof(int));
    t[0] = -1; t[1] = -1;

    // pas le courage de faire mieux
    for (int i = 0; i < size; i += 1)
    {
        for (int j = 0; j < i; j += 1)
        {
            if (table[i] == table[j])
            {
                t[0] = i; t[1] = j;
                return t;
            }
        }
    }

    return t;
}

// Exercice 56
int premierabsent(int* table, int size)
{
    if (size == 0) return 0;

    // start by geting every different values in an hash map
    HashTable* hash_table = create_table(size);

    // Insert all elements into the hash table
    for (int i = 0; i < size; i += 1)
        insert_or_update_table(hash_table, table[i], 1);

    // Find the smallest missing natural number
    for (int i = 0; i <= size; i += 1)
    {
        if (get_count(hash_table, i) == 0)
        {
            free_table(hash_table);
            return i;
        }
    }

    free_table(hash_table);
    return size + 1;
}

// Exercice 59
int evaluationHL(Card hand[13])
{
    // Card values
    char* colors = "PCKT"; // Pique, Coeur, Carreau, Trèfle

    // High Card Points
    int H = 0;
    int color_points[4] = { 0, 0, 0, 0 };

    for (int i = 0; i < 13; i += 1)
    {
        if (strcmp(hand[i].value, "A") == 0) H += 4;
        if (strcmp(hand[i].value, "R") == 0) H += 3;
        if (strcmp(hand[i].value, "D") == 0) H += 2;
        if (strcmp(hand[i].value, "V") == 0) H += 1;

        // count the number of cards for each color
        for (int j = 0; j < 4; j += 1)
        {
            if (strcmp(hand[i].color, &colors[j]) == 0)
            {
                color_points[j] += 1;
                break;
            }
        }
    }

    // je calcule comme j'ai vu qu'on faisait
    // mais j'ai pas compris l'histoire d'importance de l'attribution des "L"
    int L = 0;

    for (int i = 0; i < 4; i += 1)
    {
        if (color_points[i] <= 5) L += 1;
        else if (color_points[i] == 6) L += 2;
        else if (color_points[i] >= 7) L += 3;
    }

    return H + L;
}*/