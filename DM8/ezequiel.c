#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct IntTree { int value; int size; struct IntTree** children; };

struct Iterator { int value; struct Iterator* next; };

struct HashNode { int key; int count; struct HashNode* next; };
struct HashTable { int size; struct HashNode** buckets; };

// Typedefs
typedef struct IntTree IntTree;

typedef struct Iterator Iterator;

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

// Utils
void print_array_int(int* array, int size)
{
    for (int i = 0; i < size; i += 1) printf("%d ", array[i]);
    printf("\n");
}

// Tree
void __print_tree_(IntTree* tree, int depth) {
    if (!tree) return;

    for (int i = 1; i < depth; i++) printf("  ");
    printf("%s%d\n", depth == 0 ? "" : "└─ ", tree->value);

    for (int i = 0; i < tree->size; i++)
        __print_tree_(tree->children[i], depth + 1);
}

void print_tree(IntTree* tree) {
    __print_tree_(tree, 0);
}

IntTree* create_tree(int value, int size)
{
    IntTree* tree = malloc(sizeof(IntTree));

    tree->value = value;
    tree->size = size;   // size == 0 => NULL
    tree->children = malloc(size * sizeof(IntTree*));

    return tree;
}

void free_tree(IntTree* tree)
{
    if (!tree) return;

    for (int i = 0; i < tree->size; i += 1)
        free_tree(tree->children[i]);

    free(tree->children);
    free(tree);
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
}

// HashTable
HashTable* create_table(int size)
{
    HashTable* table = malloc(sizeof(HashTable));

    table->buckets = malloc(size * sizeof(HashNode*));
    table->size = size;

    for (int i = 0; i < size; i += 1) table->buckets[i] = NULL;
    return table;
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

void insert_or_increment_table(HashTable* table, int key)
{
    int index = key % table->size;
    HashNode* node = table->buckets[index];

    while (node)
    {
        if (node->key == key)
        {
            node->count += 1;
            return;
        }

        node = node->next;
    }

    HashNode* new_node = malloc(sizeof(HashNode));

    new_node->key = key;
    new_node->count = 1;
    new_node->next = table->buckets[index];

    table->buckets[index] = new_node;
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

bool exists(HashTable* table, int key)
{
    int index = key % table->size;
    HashNode* node = table->buckets[index];

    while (node)
    {
        if (node->key == key) return true;
        node = node->next;
    }

    return false;
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

// Functions
// Exercice 70 :
bool cycle(int* t, int size)
{
    // Check if the array is valid
    for (int i = 0; i < size; i += 1)
    {
        if (t[i] < 0 && t[i] >= size)
        {
            printf("Invalid array\n");
            return false;
        }
    }

    // Trivial case
    if (size == 0) return true;

    // So, a partition of the positive integers set...?

    // Use HashTable to store the values (as usual :p)
    HashTable* table = create_table(size);
    for (int i = 0; i < size; i += 1) insert_or_increment_table(table, t[i]);

    // Check if there's a cycle
    // ... ?

    free_table(table);
    return false;
}

// Exercice 71 :
bool idem(int* t, int size)
{
    // ;-;
    return false;
}

// Exercice 72 :
// ...

// Exercice 73 :
int nombrediviseurs(int n)
{
    if (n < 1) return 0; // n must be a postive non-zero integer
    if (n == 1) return n;

    int sqrt_n = sqrt(n); // check if we can use this function
    int count = 0;

    for (int i = 1; i <= sqrt_n; i += 1)
        if (n % i == 0) count += 1;

    return (count << 1) - (sqrt_n * sqrt_n == n ? 1 : 0);
}

// Exercice 74 :
// ...

// Exercice 75 :
char* ptm(int n)
{
    if (n < 0)
    {
        printf("Invalid number\n");
        return NULL;
    }

    // Init answer
    int length = 1 << n;
    char* str = malloc((length + 1) * sizeof(char));

    str[0] = '0';

    // Fill the answer string
    for (int i = 1, j = 1; i <= length; i += 1)
    {
        if (i >> 1 == j) j <<= 1;
        str[i] = '1' - (str[i - j] - '0');
    }

    str[length] = '\0';
    return str;
}

// Exercice 76 :
int zerosfact(int n)
{
    if (n < 5) return 0;

    // Using the Legendre's formula and knowing that the number
    // of 2s is always greater than the number of 5s

    int count = 0;
    int i = 5;

    while (n >= i)
    {
        count += n / i;
        i *= 5;
    }

    return count;
}

// Exercice 77 :
int hauteurarbre(IntTree* tree)
{
    if (!tree) return 0;

    int max = 0;

    for (int i = 0; i < tree->size; i += 1)
    {
        int height = hauteurarbre(tree->children[i]);
        if (height > max) max = height;
    }

    return 1 + max;
}

// Exercice 78 :
// ...

// Exercice 79 :
// ...

// Tests
int main()
{
    // Exercice 70
    printf("Exercice 70 : ?\n\n");

    // Exercice 71
    printf("Exercice 71 : ?\n\n");

    // Exercice 72
    printf("Exercice 72 : ?\n\n");

    // Exercice 73
    int ex73[6] = { 0, 1, 25, 3, 6, 42 };

    for (int i = 0; i < 6; i += 1)
        printf("Exercice 73 : %d\n", nombrediviseurs(ex73[i]));

    printf("\n");

    // Exercice 74
    printf("Exercice 74 : ?\n\n");

    // Exercice 75
    for (int i = 0; i < 8; i += 1)
    {
        char* ptm_o = ptm(i);
        printf("Exercice 75 : %s\n", ptm_o);
        free(ptm_o);
    }

    printf("\n");

    // Exercice 76
    printf("Exercice 76 : %d\n", zerosfact(3));   // 0
    printf("Exercice 76 : %d\n", zerosfact(5));   // 1

    for (int i = 10; i < 1001; i *= 10)
        printf("Exercice 76 : %d\n", zerosfact(i));

    // 2, 24, 249 (j'ai dénombré à la main...)
    printf("\n");

    // Exercice 77
    IntTree* tree = create_tree(1, 2);

    tree->children[0] = create_tree(2, 1);
    tree->children[0]->children[0] = create_tree(3, 0);

    tree->children[1] = create_tree(4, 2);
    tree->children[1]->children[0] = create_tree(5, 0);
    tree->children[1]->children[1] = create_tree(6, 0);

    printf("Exercice 77 : %d\n", hauteurarbre(NULL)); // 0
    print_tree(NULL);

    printf("Exercice 77 : %d\n", hauteurarbre(tree)); // 3
    print_tree(tree);

    printf("Exercice 77 : %d\n", hauteurarbre(tree->children[0])); // 2
    print_tree(tree->children[0]);

    printf("Exercice 77 : %d\n", hauteurarbre(tree->children[1]->children[0])); // 1
    print_tree(tree->children[1]->children[0]);

    free_tree(tree);
    printf("\n");

    // Exercice 78
    printf("Exercice 78 : ?\n\n");

    // Exercice 79
    printf("Exercice 79 : ?\n\n");

    return 0;
}

// Sources :
// Suite de Prouhet-Thue-Morse : https://fr.wikipedia.org/wiki/Suite_de_Prouhet-Thue-Morse
// Formule de Legendre (valuation p-adique de la factorielle) : https://fr.wikipedia.org/wiki/Formule_de_Legendre
