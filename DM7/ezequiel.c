#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Fraction { int num; int den; };                 // exo 63
struct Iterator { int value; struct Iterator* next; }; // exo 64

struct HashNode { int key; int count; struct HashNode* next; };
struct HashTable { int size; struct HashNode** buckets; };

// Typedefs
typedef struct Fraction Fraction;
typedef struct Iterator Iterator;

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

// Utils
void print_array_int(int* array, int size)
{
    for (int i = 0; i < size; i += 1) printf("%d ", array[i]);
    printf("\n");
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* quicksort(int* t, int size)
{
    if (size < 2) return t;

    int pivot = t[size / 2];
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        while (t[left] < pivot) left += 1;
        while (t[right] > pivot) right -= 1;

        if (left <= right)
        {
            swap(&t[left], &t[right]);

            left += 1;
            right -= 1;
        }
    }

    if (right > 0) quicksort(t, right + 1);
    if (left < size) quicksort(t + left, size - left);

    return t;
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
// Exercice 60 :
int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int mcnuggets(int a, int b) // O(min(a,b))
{
    // Use Frobenius number theorem (McNugget numbers) to simplify the problem
    // Check if the number is a McNugget number and return it
    if (gcd(a, b) == 1) return a * b - a - b;

    // Otherwise, error (infinite case)
    printf("Error: infinite case\n");
    exit(1);
}

// Exercice 61 :
bool existesomme(int* t, int size) // O(n(n-1)/2 + n) => O(n^2)
{
    // Add all possible sums (with distinct indexes) to a hash table
    HashTable* table = create_table(size);

    for (int i = 0; i < size; i += 1)
        for (int j = i + 1; j < size; j += 1)
            insert_or_update_table(table, t[i] + t[j], 1);

    // Check if the sum exists in the hash table
    bool val = false;

    for (int i = 0; i < size; i += 1)
        if (exists(table, t[i])) { val = true; break; }

    // Free the hash table and return the result
    free_table(table);
    return val;
}

// Exercice 62 :
int fincommune(char* a, char* b) // O(n)
{
    int len_a = strlen(a);
    int len_b = strlen(b);

    // Get the minimum length between the two strings
    int len = len_a < len_b ? len_a : len_b;

    // Compare the strings from the end to the beginning
    for (int i = 0; i < len; i += 1)
        if (a[len_a - i - 1] != b[len_b - i - 1]) return i;

    return len;
}

// Exercice 63 :
bool simplifiable(Fraction* t, int size) // O(n^2)
{
    // Check for each fraction if it can be simplified into an other one in the array
    for (int i = 0; i < size; i += 1)
    {
        Fraction f1 = t[i];

        for (int j = 0; j < size; j += 1)
        {
            // Skip the same fraction
            if (i == j) continue;

            // Compare the current fraction with the others
            Fraction f2 = t[j];
            if (f1.num * f2.den == f1.den * f2.num) return true;
        }
    }

    return false;
}

// Exercice 64 :
Iterator* miroirlc(Iterator* l)
{
    // Create a new linked list with the same values but in reverse order
    Iterator* new_list = NULL;

    while (l)
    {
        // Replace the head of the new list with the current value
        Iterator* new_iterator = create_iterator(l->value);

        new_iterator->next = new_list;
        new_list = new_iterator;

        // Then, move to the next value
        l = l->next;
    }

    return new_list;
}

// Exercice 65 :
int sommeminmax(int* t, int size)
{
    // Assume that the size is even
    // Sort the array with a quicksort algorithm

    // Trivial cases
    if (size == 0) return 0;
    if (size == 2) return t[1];

    // NPMA => Not Possible to Make deux fou-A the same error :p
    int* sorted = malloc(size * sizeof(int));
    for (int i = 0; i < size; i += 1) sorted[i] = t[i];

    quicksort(sorted, size);

    // Free the sorted array and return the wanted value
    int sum = 0;
    for (int i = 0; i < size; i += 2) sum += sorted[i];

    free(sorted);

    return sum;
}

// Exercice 66 :
int medianfreq(int* t, int size)
{
    // Trivial cases
    if (size < 3) return 0;

    // Store each value in a hash table with its frequency
    HashTable* table = create_table(size);

    for (int i = 0; i < size; i += 1)
        insert_or_update_table(table, t[i], get_count(table, t[i]) + 1);

    // Get the highest frequency
    int max = 0;

    for (int i = 0; i < size; i += 1)
    {
        int count = get_count(table, t[i]);
        if (count > max) max = count;
    }

    // Find all values with the highest frequency
    int countMax = 0;

    for (int i = 0; i < table->size; i += 1)
        if (get_count(table, i) == max) countMax += 1;

    // Get the index and values of each value with the highest frequency
    int* values = malloc(countMax * sizeof(int));

    for (int i = 0, j = 0; i < table->size; i += 1)
        if (get_count(table, i) == max) { values[j] = i; j += 1; }

    // Get the index of each value with the highest frequency
    int* indexes = malloc(countMax * max * sizeof(int));
    int* indexesSum = malloc(countMax * sizeof(int));

    for (int i = 0; i < countMax; i += 1)
    {
        int index = 0;
        indexesSum[i] = 0;

        for (int j = 0; j < size; j += 1)
        {
            if (t[j] == values[i])
            {
                indexes[i * max + index] = j;
                indexesSum[i] += j;
                index += 1;
            }
        }
    }

    // Get the greatest sum and if there are multiple max sums,
    // get the one with the smallest median index
    int maxSum = 0;
    int minMedian = size;

    for (int i = 0; i < countMax; i += 1)
    {
        int medianIndex = max / 2 - (max % 2 == 0 ? 1 : 0);
        int medianValue = indexes[i * max + medianIndex];

        if (indexesSum[i] > maxSum)
        {
            maxSum = indexesSum[i];
            minMedian = medianValue;
        }
        else if (indexesSum[i] == maxSum && medianValue < minMedian)
        {
            minMedian = medianValue;
        }
    }

    // Freeeeeeeeee
    free(values);
    free(indexes);
    free(indexesSum);

    free_table(table);

    return minMedian;
}

// Exercice 67 :
int niederschaeffolsheim(char* s)
{
    // Check if the string is empty
    if (s[0] == '\0') return 0;

    // Create a new iterator, and store every index where a word starts
    Iterator* iterator = create_iterator(s[0] == ' ' ? 1 : 0);

    for (int i = 1; s[i] != '\0'; i += 1)
    {
        if (s[i] == ' ') add_iterator(iterator, i);
        else if (s[i + 1] == '\0') add_iterator(iterator, i + 1);
    }

    // Get the greatest gap between two words, and ignore words with a length of 0
    int max = 0;

    while (iterator->next)
    {
        // depending on the last character of the word
        int correction = (iterator->value < 2 && !iterator->next->next) ? 0 : 1;

        int diff = iterator->next->value - iterator->value - correction;
        if (diff > max) max = diff;

        // to avoid memory leaks
        Iterator* next = iterator->next;
        free(iterator);

        iterator = next;
    }

    // Free the last iterator and return the result
    free(iterator);
    return max;
}

// Exercice 68 :
bool prime(int n)
{
    if (n < 2) return false;
    if (n < 4) return true;

    if (n % 2 == 0) return false;

    for (int i = 3; i <= n / 2; i += 2) // avec la racine, ç'aurait été mieux
        if (n % i == 0) return false;

    return true;
}

char* kneckes(char* s)
{
    // Check if the string is empty
    if (s[0] == '\0' || (s[0] == ' ' && s[1] == '\0'))
    {
        char* result = malloc(7 * sizeof(char));
        strcpy(result, "hopla");
        return result;
    }

    // Create a new iterator, and store every index where a word starts
    Iterator* iterator = create_iterator(s[0] == ' ' ? 1 : 0);
    int string_length = 1;

    for (int i = 1; s[i] != '\0'; i += 1)
    {
        if (s[i] == ' ') add_iterator(iterator, i);
        else if (s[i + 1] == '\0') add_iterator(iterator, i + 1);

        string_length += 1;
    }

    // Insert "hopla" between each word which index is prime
    int i = 0;

    Iterator* indexes = create_iterator(0);
    int length = 0;

    while (iterator)
    {
        if (prime(i))
        {
            add_iterator(indexes, iterator->value);
            length += 1;
        }

        // to avoid memory leaks
        Iterator* next = iterator->next;
        free(iterator);

        iterator = next;
        i += 1;
    }

    free(iterator);

    // Create a new string with the new words
    int new_length = length * 6 + string_length + 1;
    char* result = malloc(new_length * sizeof(char));

    int j = 0;

    // insert "hopla" before each word which index is prime
    for (int i = 0; i < string_length; i += 1)
    {
        if (indexes->next && indexes->next->value == i)
        {
            result[j] = ' '; j += 1;
            result[j] = 'h'; j += 1;
            result[j] = 'o'; j += 1;
            result[j] = 'p'; j += 1;
            result[j] = 'l'; j += 1;
            result[j] = 'a'; j += 1;

            // Avoid memory leaks
            Iterator* next = indexes->next;
            free(indexes);
            indexes = next;
        }

        result[j] = s[i];
        j += 1;
    }

    result[j] = '\0';

    // Free and return
    free_iterator(indexes);
    return result;
}

// Tests
int main()
{
    // Exercice 60
    printf("Exercice 60 : %d\n\n", mcnuggets(4, 7));

    // Exercice 61
    int t1[] = {1, 2, 3, 4, 5};
    int t2[] = {2, 2, 6, 12};

    printf("Exercice 61 : %s\n", existesomme(t1, 5) ? "true" : "false");
    printf("Exercice 61 : %s\n", existesomme(t2, 4) ? "true" : "false");
    printf("\n");

    // Exercice 62
    printf("Exercice 62 : %d\n", fincommune("hello", "world"));
    printf("Exercice 62 : %d\n", fincommune("mister", "master"));
    printf("\n");

    // Exercice 63
    Fraction f1 = {1, 2};
    Fraction f2 = {2, 4};
    Fraction f3 = {3, 4};
    Fraction f4 = {4, 5};

    Fraction t3[] = {f1, f2, f3};
    Fraction t4[] = {f1, f3, f4};

    printf("Exercice 63 : %s\n", simplifiable(t3, 3) ? "true" : "false");
    printf("Exercice 63 : %s\n", simplifiable(t4, 3) ? "true" : "false");
    printf("\n");

    // Exercice 64
    Iterator* l1 = create_iterator(1);
    for (int i = 2; i <= 5; i += 1) add_iterator(l1, i);

    Iterator* l2 = miroirlc(l1);

    printf("Exercice 64 : [");
    print_iterator(l1);
    printf("] à pour chaîne miroir : [");
    print_iterator(l2);
    printf("]\n\n");

    free_iterator(l1);
    free_iterator(l2);

    // Exercice 65
    int t5[] = {29, 59, 95, 80, 96, 92, 37, 67, 77, 73, 28, 30, 54, 100, 65, 42, 38, 94, 27, 62};
    printf("Exercice 65 : %d\n\n", sommeminmax(t5, 20));

    // Exercice 66
    int t6[] = {7, 8, 2, 8, 1, 10, 4, 3, 3, 1, 0, 3, 7, 1, 7, 5, 10, 2, 9, 9};
    printf("Exercice 66 : %d\n\n", medianfreq(t6, 20));

    // Exercice 67
    printf("Exercice 67 : %d\n", niederschaeffolsheim(" hello niederschaeffolsheim world hopla "));
    printf("Exercice 67 : %d\n", niederschaeffolsheim(" hello "));
    printf("Exercice 67 : %d\n", niederschaeffolsheim(" hello"));
    printf("Exercice 67 : %d\n", niederschaeffolsheim("hello "));
    printf("Exercice 67 : %d\n", niederschaeffolsheim("hello"));
    printf("Exercice 67 : %d\n", niederschaeffolsheim(""));
    printf("\n");

    // Exercice 68
    char* s1 = kneckes("Ceci est un test de la fonction kneckes.");
    char* s2 = kneckes(" hello ");
    char* s3 = kneckes(" hello");
    char* s4 = kneckes("hello ");
    char* s5 = kneckes("hello");
    char* s6 = kneckes("");
    char* s7 = kneckes("Test hello world");

    printf("Exercice 68 : %s\n", s1); free(s1);
    printf("Exercice 68 : %s\n", s2); free(s2);
    printf("Exercice 68 : %s\n", s3); free(s3);
    printf("Exercice 68 : %s\n", s4); free(s4);
    printf("Exercice 68 : %s\n", s5); free(s5);
    printf("Exercice 68 : %s\n", s6); free(s6);
    printf("Exercice 68 : %s\n", s7); free(s7);
    printf("\n");

    return 0;
}

// Sources :
// HashTable => Copy-Past of an implementation done for a Prologin problem
// McNugget numbers => https://mathworld.wolfram.com/McNuggetNumber.html + "Coin Problem" on Wikipedia
