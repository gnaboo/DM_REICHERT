#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Structures
struct Couple { int a; int b; };

struct HashNode { int key; int count; struct HashNode* next; };
struct HashTable { int size; struct HashNode** buckets; };

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
double* q1(double* table, int size)
{
    if (!(size % 4 == 1) || size < 5)
    {
        printf("Erreur, la taille du tableau doit être de la forme 4n + 1");
        printf(" avec n un entier naturel non nul\n");
        exit(1);
    }

    // allocate memory for the quartile table
    int n = (size - 1) / 4;
    double* quartile = malloc(n * sizeof(double));

    // set the quartile values and return the table
    for (int i = 0; i < n; i += 1) quartile[i] = table[i];
    return quartile;
}

// Exercice 52
int minecart(int* table, int size)
{
    // set initial gap to the first element
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
        // Check if the first element is the same as the second
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

    // set to 1 if the key is not in the table, else increment the count
    for (int i = 0; i < size; i += 1)
        insert_or_update_table(hash_table, table[i], get_count(hash_table, table[i]) + 1);

    // Get the count of the first element as reference
    int count = hash_table->buckets[0]->count;

    for (int i = 1; i < hash_table->size; i += 1)
    {
        // If the count is different, the table is not balanced => return false
        if (hash_table->buckets[i] && hash_table->buckets[i]->count != count)
        {
            free_table(hash_table);
            return false;
        }
    }

    free_table(hash_table);
    return true;
}

// Exercice 56
int premierabsent(int* table, int size)
{
    if (size == 0) return 0;

    // get the lowest natural integer missing in the table
    int min = table[0];

    for (int i = 1; i < size; i += 1)
        if (table[i] < min) min = table[i];

    return (min > 0) ? 0 : min - 1;
}

// Exercice 57
int rpz(char* s)
{
    // "moselle" => 7 letters (3 + 2*"e" + 2*"l")

    // set string to lowercase
    for (int i = 0; s[i] != '\0'; i += 1)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;

    int counts[] = { 0, 0, 0, 0, 0 };

    // :p
    for (int i = 0; s[i] != '\0'; i += 1)
    {
        if (s[i] == 'm') counts[0] += 1;
        if (s[i] == 'o') counts[1] += 1;
        if (s[i] == 's') counts[2] += 1;
        if (s[i] == 'e') counts[3] += 1;
        if (s[i] == 'l') counts[4] += 1;
    }

    // halve the count of "e" and "l"
    counts[3] /= 2;
    counts[4] /= 2;

    // get the minimum count
    int min = counts[0];

    for (int i = 1; i < 5; i += 1)
        if (counts[i] < min) min = counts[i];

    return min;
}

// Exercice 58
int* decomp(int n)
{
    if (n < 1)
    {
        printf("Erreur, n doit être un entier naturel non nul\n");
        exit(1);
    }

    int* decomp = malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i += 1) decomp[i] = 0;

    int j = 0;

    // start by decomposing by 2 (even numbers)
    while (n % 2 == 0)
    {
        decomp[j] = 2;
        j++; n /= 2;
    }

    // then decompose by odd numbers
    for (int i = 3; i <= n && n > 1; i += 2)
    {
        while (n % i == 0)
        {
            decomp[j] = i;
            j++; n /= i;
        }
    }

    return decomp;
}

// Exercice 59
// Non

// Tests
int main()
{
    // Common variables
    double table1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1.0, 1.1, 1.2, 1.3 }; // 51
    int table2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };        // 52
    int table3[] = { 1, 2, 3, 1, 2, 4, 1, 2, 3, 1, 2 };                  // 53
    int table4[] = { 1, 2, 3, 2, 42, 42, 8, 8 };                         // 54, 55

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

    // Exercice 55
    bool balanced = equilibre(table4, 8);
    printf("Exercice 55 : %s\n", balanced ? "Oui" : "Non");

    // Exercice 56
    int absent = premierabsent(table4, 8);
    printf("Exercice 56 : %d\n", absent);

    // Exercice 57
    int min = rpz("moselle elle somme lol es 42 = 57");
    printf("Exercice 57 : %d\n", min);

    // Exercice 58
    int* decomp58 = decomp(42);

    printf("Exercice 58 : ");
    for (int i = 0; i < 41 && decomp58[i] != 0; i += 1) printf("%d ", decomp58[i]);
    printf("\n");

    free(decomp58);

    // Exercice 59
    // Juste non quoi

    return 0;
}
