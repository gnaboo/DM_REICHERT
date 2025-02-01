#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Structures
struct Couple { int a; int b; };

struct HashNode { int key; int value; struct HashNode* next; };
struct HashTable { int size; HashNode** table; };

// Typedefs
typedef struct Couple Couple;
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

    table->table = malloc(size * sizeof(HashNode*));
    table->size = size;

    for (int i = 0; i < size; i += 1) table->table[i] = NULL;
    return table;
}

void insert_or_update_table(HashTable* table, int key, int value)
{
    int index = key % table->size;
    HashNode* node = table->table[index];

    while (node)
    {
        if (node->key == key)
        {
            node->value = value;
            return;
        }

        node = node->next;
    }

    HashNode* new_node = malloc(sizeof(HashNode));

    new_node->key = key;
    new_node->value = value;
    new_node->next = table->table[index];

    table->table[index] = new_node;
}

void free_table(HashTable* table)
{
    for (int i = 0; i < table->size; i += 1)
    {
        HashNode* node = table->table[i];

        while (node)
        {
            HashNode* next = node->next;

            free(next->key);
            free(next);
        }
    }

    free(table->table);
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

    for (int b = 0; b <= 3; b += 1)
    {
        int t = n - 3 * b;
        if (t % 4 == 0) return (Couple) { a: t / 4, b };
    }

    // si impossible (normalement, n'a pas lieu d'arriver)
    return (Couple) { -1, -1 };
}

// Exercice 51
double* q1(double* table, int size)
{
    if (!(size % 4 == 1))
    {
        printf("Erreur, la taille du tableau doit être de la forme 4n + 1\n");
        exit(1);
    }

    int n = (size - 1) / 4;
    double* quartile = malloc(n * sizeof(double));

    for (int i = 0; i < n; i += 1) quartile[i] = table[i];
    return quartile;
}

// Exercice 52
int minecart(int* table, int size)
{
    int gap = abs(table[0]);

    for (int i = 0; i < size; i += 1)
    {
        int g = abs(table[i] - i);
        if (g < gap) gap = g;
    }

    return gap;
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

    for (int i = 1; i < size; i += 1)
    {
        if (table[i] == table[i - 1])
        {
            t[0] = i; t[1] = i - 1;
            break;
        }
    }

    return t;
}

// Exercice 55
bool equilibre(int* table, int size)
{
    // This function is implemented with an hash table
    // An other way to implement it, could be to sort the table before counting the elements

    HashTable* hash_table = create_table(size);

    for (int i = 0; i < size; i += 1)
        insert_or_update_table(hash_table, table[i], 1);

    // 
}

// Tests
int main()
{
    // Common variables
    double table1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1.0, 1.1, 1.2, 1.3 };
    int table2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1.0, 1.1, 1.2, 1.3 };
    int table3[] = { 1, 2, 3, 1, 2, 4, 1, 2, 3, 1, 2 };
    int table4[] = { 1, 2, 3, 2, 42, 42, 8, 8 };

    // Exercice 50
    Couple tab50 = tables(9);
    printf("Exercice 50 : %d %d\n", tab50.a, tab50.b);

    // Exercice 51
    double* quartile = q1(table1, 13);

    printf("Exercice 51 : ");
    print_array_float(quartile, 3);

    free(quartile);

    // Exercice 52
    int gap = minecart(table2, 13);
    printf("Exercice 52 : %d\n", gap);

    // Exercice 53  
    int premier = premiercommepremier(table3, 11);
    printf("Exercice 53 : %d\n", premier);

    // Exercice 54
    int* avant = premiercommeavant(table4, 8);

    printf("Exercice 54 : ");   
    print_array_int(avant, 2);

    free(avant);

    // 

    return 0;
}
