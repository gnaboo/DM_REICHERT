#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Les macros suivantes sont gardées malgré l'HP puisque non utiles aux fonctionnement
// des algorithmes principaux (ceux des exercices), mais utiles pour le debug.

/* Newline macro */
#define print_newline printf("\n")
/* Print a Node */
#define print_node(node) __print_node_(node, 0, 1), print_newline
/* String of bool */
#define str_of_bool(value) (value ? "true" : "false")

// Structures
struct Node { int count; struct Node** children; };
struct Graph { int* vertices; bool** edges; int size; };
struct Couple86 { char* str; double nb; };
struct IntCouple { int a; int b; };

struct Iterator { double value; struct Iterator* next; };
struct Queue { int node; int depth; struct Queue* next; };
struct HashNode { int key; int value; struct HashNode* next; };
struct HashTable { int size; struct HashNode** buckets; };

// Typedefs
typedef struct Node Node;
typedef struct Graph Graph;
typedef struct Couple86 Couple86;
typedef struct IntCouple IntCouple;

typedef struct Iterator Iterator;
typedef struct Queue Queue;
typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

// Utils
void print_array_int(int* array, int size)
{
    int start = size < 0 ? 1 : 0;
    if (size < 0) size = array[0];

    printf("[");

    for (int i = start; i < size + start; i += 1)
        printf("%d%s", array[i], (i < size + start - 1 ? ", " : ""));

    printf("]\n");
}

void print_array_double(double* array, int size)
{
    int start = size < 0 ? 1 : 0;
    if (size < 0) size = array[0];

    printf("[");

    for (int i = start; i < size + start; i += 1)
        printf("%g%s", array[i], (i < size + start - 1 ? ", " : ""));

    printf("]\n");
}

void print_matrix(int** matrix, int rows, int cols)
{
    printf("[\n");

    for (int i = 0; i < rows; i += 1)
    {
        if (matrix[i] == NULL) {
            printf("  NULL,\n");
            continue;
        }

        printf("  [");

        for (int j = 0; j < cols; j += 1) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(", ");
        }
    
        printf("],\n");
    }

    printf("]\n");
}

int** matrix_from_array(int* array, int rows, int cols)
{
    int** matrix = malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i += 1)
    {
        matrix[i] = malloc(cols * sizeof(int));

        for (int j = 0; j < cols; j += 1)
            matrix[i][j] = array[i * cols + j];
    }

    return matrix;
}

void free_matrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; i += 1)
        free(matrix[i]);
    free(matrix);
}

void print82(int** matrix, int** result, int* indexes, int rows, int col1, int col2)
{
    printf("Exercice 82 : \nInput: ");
    print_matrix(matrix, rows, col1);
    printf("Selecting indexes: ");
    if (col2 > 0) print_array_int(indexes, col2);
    else printf("(any)\n");
    printf("Output: ");
    print_matrix(result, rows, col2);
    print_newline;
}

void print_couples86(Couple86** couples, int size)
{
    printf("{\n");

    for (int i = 0; i < size; i += 1)
        printf("  {\"%s\" : %g},\n", couples[i]->str, couples[i]->nb);

    printf("}\n");
}

char*** make_cards(char* game) {
    char*** cards = malloc(8 * sizeof(char**));
    for (int i = 0; i < 8; i += 1) {
        cards[i] = malloc(4 * sizeof(char*));
    }

    int index = 0;
    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 4; j += 1) {
            if (game[index + 1] == '1' && game[index + 2] == '0') {
                cards[i][j] = malloc(4 * sizeof(char));
                for (int k = 0; k < 3; k += 1) cards[i][j][k] = game[index + k];
                cards[i][j][3] = '\0';

                index += 3;
            } else {
                cards[i][j] = malloc(3 * sizeof(char));
                cards[i][j][0] = game[index];
                cards[i][j][1] = game[index + 1];
                cards[i][j][2] = '\0';

                index += 2;
            }
        }
    }

    return cards;
}

// Node
Node* create_node(int size)
{
    Node* node = malloc(sizeof(Node));

    node->count = size;
    node->children = malloc(size * sizeof(Node*));

    for (int i = 0; i < size; i += 1)
        node->children[i] = NULL;

    return node;
}

void free_node(Node* node)
{
    if (node == NULL) return;

    for (int i = 0; i < node->count; i += 1)
        free_node(node->children[i]);

    free(node->children);
    free(node);
}

void __print_node_(Node* node, int level, int is_last)
{
    if (node == NULL) return;

    for (int i = 0; i < level - 1; i += 1) printf("  ");
    if (level > 0) printf(is_last ? "└─ " : "├─ ");
    printf("%d\n", node->count);

    for (int i = 0; i < node->count; i += 1) {
        int last_child = (i == node->count - 1);
        __print_node_(node->children[i], level + 1, last_child);
    }
}

// Graph
Graph* init_graph(int size)
{
    if (size <= 0)
    {
        printf("Error: Invalid size\n");
        exit(1);
    }

    Graph* graph = malloc(sizeof(Graph));

    graph->size = size;
    graph->vertices = malloc(size * sizeof(int));
    graph->edges = malloc(size * sizeof(bool*));

    for (int i = 0; i < size; i += 1)
    {
        graph->vertices[i] = i;
        graph->edges[i] = malloc(size * sizeof(bool));

        for (int j = 0; j < size; j += 1)
            graph->edges[i][j] = false;
    }

    return graph;
}

void free_graph(Graph* graph)
{
    for (int i = 0; i < graph->size; i += 1)
        free(graph->edges[i]);

    free(graph->edges);
    free(graph->vertices);
    free(graph);
}

// Iterator
Iterator* create_iterator(double value)
{
    Iterator* iterator = malloc(sizeof(Iterator));

    iterator->value = value;
    iterator->next = NULL; // null pointer at the end

    return iterator;
}

Iterator* add_iterator(Iterator* iterator, double value)
{
    if (iterator == NULL)
        return create_iterator(value);

    Iterator* new_iterator = create_iterator(value);
    Iterator* current = iterator;

    while (current->next) current = current->next;
    current->next = new_iterator;

    return iterator;
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

int* iterator_to_int_array(Iterator* iterator, int size)
{
    // Check if the iterator is empty
    if (iterator == NULL) return NULL;

    // Convert the iterator to an array
    int* array = malloc((size + 1) * sizeof(int));

    for (int i = 1; i <= size; i += 1)
    {
        // Check if the iterator is empty
        if (iterator == NULL)
        {
            size = i - 1;
            break;
        }

        // Add the value to the array
        array[i] = (int) iterator->value;
        iterator = iterator->next;
    }

    // Set the first element to the size of the array
    array[0] = size;
    return array;
}

void value_add_last_iterator(Iterator* iterator, double value)
{
    // Check if the iterator is empty
    if (iterator == NULL) return;

    // Add the value to the last element of the iterator
    while (iterator->next) iterator = iterator->next;
    iterator->value += value;
}

void print_iterator(Iterator* iterator)
{
    while (iterator)
    {
        printf("%g ", iterator->value);
        iterator = iterator->next;
    }

    printf("\n");
}

// Queue
Queue* enqueue(Queue* queue, int node, int depth)
{
    Queue* new_queue = malloc(sizeof(Queue));

    new_queue->node = node;
    new_queue->depth = depth;
    new_queue->next = NULL;

    if (queue == NULL) return new_queue;

    Queue* tail = queue;

    while (tail->next) tail = tail->next;
    tail->next = new_queue;

    return queue;
}

Queue* dequeue(Queue* queue, int* node, int* depth)
{
    if (queue == NULL) return NULL;

    *node = queue->node;
    *depth = queue->depth;

    Queue* next = queue->next;
    free(queue);

    return next;
}

// Couples (Exercice 86)
Couple86* create_couple86(char* str, double nb)
{
    Couple86* couple = malloc(sizeof(Couple86));

    couple->str = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(couple->str, str);
    couple->nb = nb;

    return couple;
}

void free_couple86(Couple86* couple)
{
    if (couple == NULL) return;

    free(couple->str);
    free(couple);
}

void free_couples86(Couple86** couples, int size)
{
    for (int i = 0; i < size; i += 1)
        free_couple86(couples[i]);
    free(couples);
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
    // (this version can handle negative keys)
    return (key % table->size + table->size) % table->size;
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
    if (size <= 0)
    {
        printf("Error: Invalid size\n");
        exit(1);
    }

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
    // Exclude size <= 0
    if (size <= 0)
    {
        printf("Error: Invalid size\n");
        exit(1);
    }

    // Use the hashtable to store the already computed sums
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

// Exercice 82 :
/**
 * @param matrix The sequence of arrays containing numbers
 * @param n The number of arrays
 * @param p The size of each array
 * @param indexes The indexes of the arrays to select
 * @param k The number of indexes
 * @return The selected elements from the arrays
 */
int** selectfrom(int** matrix, int n, int p, int* indexes, int k)
{
    // Trivial cases
    if (n < 0 || p < 0 || k < 0)
    {
        printf("Error: n, p and k must be positive integers\n");
        exit(1);
    }
    else if (n == 0) return NULL;
    else if (k > p && p > 0)
    {
        printf("Error: k must be less than or equal to p\n");
        exit(1);
    }
    else if (p == 0 || k == 0 || k > p)
    {
        int** result = malloc(n * sizeof(int*));
        for (int i = 0; i < n; i += 1) result[i] = (int*) NULL;

        return result;
    }

    // Initialize the result array
    int** result = malloc(n * sizeof(int*));

    // Fill the result array with the selected elements
    for (int i = 0; i < n; i += 1)
    {
        result[i] = malloc(k * sizeof(int));

        for (int j = 0; j < k; j += 1)
            result[i][j] = matrix[i][indexes[j]];
    }

    return result;
}

// Exercice 83
int strahler(Node* node)
{
    if (node == NULL) return 0;

    int max = 0;
    int count = 0;

    for (int i = 0; i < node->count; i += 1)
    {
        int child_value = strahler(node->children[i]);

        if (child_value > max) {
            max = child_value;
            count = 1;
        }
        else if (child_value == max) count += 1;
    }

    return (count == 0 ? 1 : max) + (count > 1 ? 1 : 0);
}

// Exercice 84
int* dist_n(Graph* G, int start, int n)
{
    // Trivial cases
    if (G == NULL || n == 0 || G->size == 0)
    {
        return NULL;
    }
    else if (n < 0 || start < 0 || start >= G->size)
    {
        printf("Error: Invalid parameters.\n");
        exit(1);
    }

    // Initialize the result into an iterator
    bool* visited = malloc(G->size * sizeof(bool));
    for (int i = 0; i < G->size; i += 1) visited[i] = false;

    // get all the nodes at distance n from the start node (repetitions allowed)
    Iterator* result = NULL;
    Queue* queue = enqueue(NULL, start, 0);

    int elements_count = 0;

    while (queue)
    {
        // Dequeue the first element
        int current;
        int depth;

        queue = dequeue(queue, &current, &depth);

        // If the current depth is equal to n, add the current node to the result
        if (depth == n)
        {
            if (!visited[current])
            {
                result = add_iterator(result, current);

                visited[current] = true;
                elements_count += 1;
            }

            continue;
        }

        if (depth < n)
            for (int i = 0; i < G->size; i += 1)
                if (G->edges[current][i])
                    queue = enqueue(queue, i, depth + 1);
    }

    // Convert the iterator to an array
    int* result_array = iterator_to_int_array(result, elements_count);

    free_iterator(result);
    free(visited);

    return result_array;
}

// Exercice 85
double* unitaire(double* tab, int size)
{
    if (size <= 0)
    {
        printf("Error: Invalid size\n");
        exit(1);
    }

    // Init the Pnomial
    double* P = malloc((size + 1) * sizeof(double));
    double* temp = malloc((size + 1) * sizeof(double));

    for (int i = 0; i <= size; i += 1) P[i] = 0;
    P[0] = 1;

    for (int i = 0; i < size; i += 1)
    {
        double root = tab[i];

        for (int j = 0; j <= size; j += 1) temp[j] = P[j];
        for (int j = 0; j <= i + 1; j += 1) P[j] = 0;

        for (int j = 0; j <= i; j += 1)
        {
            P[j + 1] += temp[j];
            P[j] -= root * temp[j];
        }
    }

    free(temp);
    return P;
}

// Exercice 86
void swap_couples(Couple86* a, Couple86* b)
{
    Couple86 temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort_couples(Couple86** tab, int size, int start, int end)
{
    // sort the array of couples by the first element (str, lexicographically)
    if (start < end)
    {
        int pivot = start;
        int i = start + 1;
        int j = end;

        while (i <= j)
        {
            while (i <= end && strcmp(tab[i]->str, tab[pivot]->str) <= 0) i += 1;
            while (j >= start && strcmp(tab[j]->str, tab[pivot]->str) > 0) j -= 1;

            if (i < j) swap_couples(tab[i], tab[j]);
        }

        swap_couples(tab[pivot], tab[j]);

        quicksort_couples(tab, size, start, j - 1);
        quicksort_couples(tab, size, j + 1, end);
    }
}

Couple86** avggroupby(Couple86** tab, int size)
{
    if (size <= 0)
    {
        printf("Error: Invalid size\n");
        exit(1);
    }

    // Copy the array of couples to a new array
    Couple86** new_tab = malloc(size * sizeof(Couple86*));

    for (int i = 0; i < size; i += 1)
    {
        new_tab[i] = malloc(sizeof(Couple86));

        new_tab[i]->str = malloc((strlen(tab[i]->str) + 1) * sizeof(char));
        new_tab[i]->nb = tab[i]->nb;

        strcpy(new_tab[i]->str, tab[i]->str);
    }

    // Sort the array of couples by the first element (str, lexicographically)
    quicksort_couples(new_tab, size, 0, size - 1);

    // get the number of unique elements + the sum of the second element (nb)
    int unique_count = 1;

    /* Indexes of each new unique element */
    Iterator* indexes = create_iterator(0);
    /* Sums of each elements of the same group */
    Iterator* sums = create_iterator(new_tab[0]->nb);

    for (int i = 1; i < size; i += 1)
    {
        // if the current element is different from the previous one
        // increment the unique count, add the current element to the indexes
        // and add the current element to the sums
        if (strcmp(new_tab[i]->str, new_tab[i - 1]->str) != 0)
        {
            unique_count += 1;
            indexes = add_iterator(indexes, i);
            sums = add_iterator(sums, new_tab[i]->nb);
        }
        else
        {
            // if the current element is the same as the previous one
            // increment the sum of the furthest element
            value_add_last_iterator(sums, new_tab[i]->nb);
        }
    }

    // create the new array of couples (result)
    Couple86** result = malloc(unique_count * sizeof(Couple86*));

    for (int i = 0; i < unique_count; i += 1)
    {
        // get the count of the current element (difference between the indexes)
        int count = 0;
        if (i == unique_count - 1) count = size - indexes->value;
        else count = indexes->next->value - indexes->value;

        result[i] = create_couple86(new_tab[(int) indexes->value]->str, sums->value / count);

        // free and update the indexes and sums
        Iterator* next_index = indexes->next;
        Iterator* next_sum = sums->next;

        free(indexes);
        free(sums);

        indexes = next_index;
        sums = next_sum;
    }

    // free the old array of couples
    free_couples86(new_tab, size);
    return result;
}

// Exercice 87
int cmp_substr_legalement(char* str, int start, int end, int len)
{
    // Compare the substrings without using "[p+1]" (pointer arithmetic)
    for (int i = 0; i < len; i += 1)
        if (str[start + i] != str[end + i])
            return 0;

    return 1;
}

IntCouple* facteurmax(char* str)
{
    int n = strlen(str);

    int best_len = 0;
    int index1 = 0;
    int index2 = 0;

    for (int len = n; len > 0; len -= 1)
    {
        if (n <= 1) break;

        for (int i = 0; i <= n - len; i += 1)
        {
            int first = -1;
            int second = -1;

            for (int j = i + 1; j <= n - len; j += 1)
            {
                if (cmp_substr_legalement(str, i, j, len) == 1)
                {
                    first = i;
                    second = j;
                    break;
                }
            }

            if (first != -1 && second != -1)
            {
                // Check if the length is greater than the best length
                if (len > best_len)
                {
                    best_len = len;
                    index1 = first;
                    index2 = second;
                }
            }
        }

        if (best_len > 0) break;
    }

    // If no substring was found, throw an printf error and return NULL
    if (best_len == 0)
    {
        // (avoid to throw an error to avoid breaking the program)
        printf("Error: No substring found 😔\n");
        return NULL;
    }

    // Create and return the result
    IntCouple* result = malloc(sizeof(IntCouple));

    result->a = index1;
    result->b = index2;

    return result;
}

// Exercice 88
void gauss(double** matrix, double* vertex, int size)
{
    // avoid the trivial cases, assume the matrix is square, and let's mute the matrix
    for (int i = 0; i < size; i += 1)
    {
        double pivot = matrix[i][i];

        if (pivot != 1)
        {
            for (int j = 0; j < size; j += 1)
                matrix[i][j] /= pivot;
            vertex[i] /= pivot;
        }

        // eliminate the other rows
        for (int k = i + 1; k < size; k += 1)
        {
            double factor = matrix[k][i];

            for (int j = i; j < size; j += 1)
                matrix[k][j] -= factor * matrix[i][j];
            vertex[k] -= factor * vertex[i];
        }
    }
}

double* hyperplan(double** vertices, int n)
{
    // Assume that `vertices` is a 2D array of size (n-1) x n
    // Check if the vertices are valid
    if (n < 1)
    {
        printf("Error: Invalid input.\n");
        exit(1);
    }

    // Get the equation of the hyperplane

    // Initialize an system of equations like Ax = B
    double** matrix = malloc((n - 1) * sizeof(double*));
    double* vertex = malloc((n - 1) * sizeof(double));

    for (int i = 0; i < n - 1; i += 1)
    {
        matrix[i] = malloc((n - 1) * sizeof(double));

        // Fill the matrix with the vertices
        for (int j = 0; j < n - 1; j += 1)
            matrix[i][j] = vertices[i][j + 1];

        // Fill the vertex with the last column of the vertices
        vertex[i] = -vertices[i][0];
    }

    // Apply the Gauss elimination method
    gauss(matrix, vertex, n - 1);

    // Inverse substitution
    double* x = malloc((n - 1) * sizeof(double));
    for (int i = n - 2; i >= 0; i -= 1)
    {
        x[i] = vertex[i];

        for (int j = i + 1; j < n - 1; j += 1)
            x[i] -= matrix[i][j] * x[j];
    }

    // Construct the hyperplane equation
    double* hyperplane = malloc(n * sizeof(double));

    hyperplane[0] = 1;
    for (int i = 0; i < n - 1; i += 1) hyperplane[i + 1] = x[i];

    // Free the memory used
    free_matrix((int**) matrix, n - 1);
    free(vertex);
    free(x);

    return hyperplane;
}

// Exercice 89
int get_card_points(char* card, char* trump)
{
    char color = card[0];
    char value = card[1];
    bool is_trump = (color == trump[0]);

    // Get the card's points
    if (value == 'Q') return 3;
    if (value == 'K') return 4;
    if (value == '1') return 10; // "10" (admit it :D)
    if (value == 'A') return 11;

    if (value == '9') return is_trump ? 14 : 0;
    if (value == 'J') return is_trump ? 20 : 2;

    return 0;
}

bool is_stronger(char* card1, char* card2, char* trump, char leading)
{
    // Get the color and value of the cards
    char color1 = card1[0];
    char value1 = card1[1];
    char color2 = card2[0];
    char value2 = card2[1];

    bool is_trump1 = (color1 == trump[0]);
    bool is_trump2 = (color2 == trump[0]);
    bool follow1 = (color1 == leading);
    bool follow2 = (color2 == leading);

    // Check if the cards are trumps
    if (is_trump1 && is_trump2)
    {
        char order_trump[9] = "J9A1KQ87";

        // Compare the values of the trumps
        for (int i = 0; i < 8; i += 1)
        {
            if (order_trump[i] == value1 && order_trump[i] == value2) return true;
            if (order_trump[i] == value1) return true;
            if (order_trump[i] == value2) return false;
        }
    }
    else if (is_trump1 || is_trump2) return is_trump1;
    else if (follow1 && !follow2) return true;
    else if (!follow1) return false;

    char order[9] = "A1KQJ987";

    for (int i = 0; i < 8; i += 1)
    {
        if (order[i] == value1 && order[i] == value2) return false;
        if (order[i] == value1) return true;
        if (order[i] == value2) return false;
    }

    return false;
}

int find_winner(char** trick, char* trump, int first_player)
{
    int best_player = first_player;
    char* best_card = trick[0];
    char leading = best_card[0];

    for (int i = 1; i < 4; i += 1)
    {
        int player = (first_player + i) % 4;
        char* card = trick[i];

        if (is_stronger(card, best_card, trump, leading))
        {
            best_player = player;
            best_card = card;
        }
    }

    return best_player;
}

bool belote(char* trump, int index, char*** cards)
{
    // Assume that the cards are contained in a 2D array of size 8 x 4
    // and that all the variables are initialized properly (valid)
    int team1 = 0;
    int team2 = 0;

    int belotePoints = -1;

    int player = (index + 1) % 4;

    for (int i = 0; i < 8; i += 1)
    {
        int winner = find_winner(cards[i], trump, player);
        int team = (winner % 2 == 0) ? 1 : 2;

        int points = 0;
        for (int j = 0; j < 4; j += 1)
        {
            // Check if the player has the "belote" or "rebelote" cards
            char cardK[3] = { trump[0], 'K', '\0' };
            char cardQ[3] = { trump[0], 'Q', '\0' };

            if (strcmp(cards[i][j], cardK) == 0 || strcmp(cards[i][j], cardQ) == 0)
            {
                int index = (player + j) % 4;

                if (belotePoints == -1) belotePoints = index;
                else if (belotePoints == index)
                {
                    if (index % 2 == 0) team1 += 20;
                    else team2 += 20;
                }
            }

            // Add the points of the cards
            points += get_card_points(cards[i][j], trump);
        }

        // Add the points of the trick (+ "10 de der" points)
        if (team == 1) team1 += points + (i == 7 ? 10 : 0);
        else team2 += points + (i == 7 ? 10 : 0);

        player = winner;
    }

    // THE END (of this function)
    return team1 > team2;
}

// Test
int main()
{
    // Exercice 80
    int tab80_1[] = { 2, 3, 4, 5, 6 };
    int tab80_2[] = { 8 };
    int tab80_3[] = { 1, 1 };
    int tab80_4[] = { 20, 42, 55, 27, 69, 55, 17, 64 };
    int tab80_5[] = { 2, 3, 7 };

    printf("Exercice 80 : %d\n", ppcm_ens(tab80_1, 5)); // 2 * 3 * 4 * 5
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_2, 1)); // 8
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_3, 2)); // 1
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_4, 8)); // (2**6)*(3**3)*5*7*11*17*23
    printf("Exercice 80 : %d\n", ppcm_ens(tab80_5, 3)); // 2 * 3 * 7 :D

    print_newline;

    // Exercice 81
    int tab81_1[] = { 1, 2, 3, 4, 5 };
    int tab81_2[] = { 1, 2, 3, -4, 5, 6 };
    int tab81_3[] = { 1, 7, 6, 4 };
    int tab81_4[] = { 1, 1 };
    int tab81_5[] = { 0 };

    printf("Exercice 81 : %s\n", str_of_bool(subsetsum(tab81_1, 5, 6)));
    // Expected: true (1 + 2 + 3 = 6 || ...)
    printf("Exercice 81 : %s\n", str_of_bool(subsetsum(tab81_2, 6, -1)));
    // Expected: true (3 - 4 = - 1 || ...)
    printf("Exercice 81 : %s\n", str_of_bool(subsetsum(tab81_3, 4, 42)));
    // Expected: false (1 + 7 + 6 + 4 = 18 < 42)
    printf("Exercice 81 : %s\n", str_of_bool(subsetsum(tab81_4, 2, 1)));
    // Expected: true (1 = 1 || ...)
    printf("Exercice 81 : %s\n", str_of_bool(subsetsum(tab81_5, 1, 5)));
    // Expected: false (0 < 5)

    print_newline;

    // Exercice 82
    int** matrix1 = matrix_from_array((int []){ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 3, 3);
    int** matrix2 = matrix_from_array((int []){ 42, 42, 42, 42 }, 4, 0);
    int** matrix3 = matrix_from_array(
        (int []){ 10, 20, 30, 40, 50,
                  11, 21, 31, 41, 51,
                  12, 22, 32, 42, 52,
                  13, 23, 33, 43, 53 },
        4, 5);

    int indexes1a[2] = { 0, 1 };
    int indexes1b[0] = {};
    int indexes2[3] = { 0, 1, 2 };
    int indexes3a[3] = { 2, 4, 1 };
    int indexes3b[5] = { 0, 1, 2, 3, 4 };

    int** result1 = selectfrom(matrix1, 3, 3, indexes1a, 2);
    int** result2 = selectfrom(matrix1, 9, 3, indexes1b, 0);
    int** result3 = selectfrom(matrix2, 4, 0, indexes2, 3);
    int** result4 = selectfrom(matrix3, 4, 5, indexes3a, 3);
    int** result5 = selectfrom(matrix3, 4, 5, indexes3b, 5);

    print82(matrix1, result1, indexes1a, 3, 3, 2);
    print82(matrix1, result2, indexes1b, 3, 3, 0);
    print82(matrix2, result3, indexes2, 4, 0, 3);
    print82(matrix3, result4, indexes3a, 4, 5, 3);
    print82(matrix3, result5, indexes3b, 4, 5, 5);

    free_matrix(matrix1, 3); free_matrix(result1, 3); free_matrix(result2, 3);
    free_matrix(matrix2, 4); free_matrix(result3, 4);
    free_matrix(matrix3, 4); free_matrix(result4, 4); free_matrix(result5, 4);

    // Exercice 83
    Node* node1a = create_node(0);
    Node* node2a = create_node(0);
    Node* node3a = create_node(0);
    Node* tree_a = create_node(3);

    tree_a->children[0] = node1a;
    tree_a->children[1] = node2a;
    tree_a->children[2] = node3a;

    Node* node1b = create_node(2);
    Node* node2b = create_node(1);
    Node* node3b = create_node(1);
    Node* node4b = create_node(0);
    Node* node5b = create_node(0);
    Node* node6b = create_node(0);
    Node* tree_b = create_node(2);

    tree_b->children[0] = node1b;
    tree_b->children[1] = node2b;
    node1b->children[0] = node3b;
    node1b->children[1] = node4b;
    node2b->children[0] = node5b;
    node3b->children[0] = node6b;

    Node* node1c = create_node(0);
    Node* node2c = create_node(0);
    Node* node3c = create_node(0);
    Node* node4c = create_node(0);
    Node* node5c = create_node(0);
    Node* node6c = create_node(0);
    Node* node7c = create_node(0);
    Node* node8c = create_node(0);
    Node* node9c = create_node(0);
    Node* node10c = create_node(0);
    Node* node11c = create_node(2);
    Node* node12c = create_node(2);
    Node* node13c = create_node(2);
    Node* node14c = create_node(2);
    Node* node15c = create_node(2);
    Node* node16c = create_node(2);
    Node* node17c = create_node(2);
    Node* node18c = create_node(2);
    Node* tree_c = create_node(2);

    node11c->children[0] = node1c;
    node11c->children[1] = node2c;
    node12c->children[0] = node3c;
    node12c->children[1] = node4c;
    node13c->children[0] = node5c;
    node13c->children[1] = node6c;
    node14c->children[0] = node7c;
    node14c->children[1] = node8c;
    node15c->children[0] = node11c;
    node15c->children[1] = node12c;
    node16c->children[0] = node13c;
    node16c->children[1] = node14c;
    node17c->children[0] = node9c;
    node17c->children[1] = node15c;
    node18c->children[0] = node16c;
    node18c->children[1] = node17c;
    tree_c->children[0] = node10c;
    tree_c->children[1] = node18c;

    Node* node1d = create_node(1);
    Node* node2d = create_node(1);
    Node* node3d = create_node(1);
    Node* node4d = create_node(0);

    node1d->children[0] = node2d;
    node2d->children[0] = node3d;
    node3d->children[0] = node4d;

    printf("Exercice 83 : %d is the Strahler number of the tree :\n", strahler(tree_a));
    print_node(tree_a); // balanced tree   ; Expected: 2

    printf("Exercice 83 : %d is the Strahler number of the tree :\n", strahler(tree_b));
    print_node(tree_b); // unbalanced tree ; Expected: 2

    printf("Exercice 83 : %d is the Strahler number of the tree :\n", strahler(tree_c));
    print_node(tree_c); // Wikipedia tree  ; Expected: 4

    printf("Exercice 83 : %d is the Strahler number of the tree :\n", strahler(node1d));
    print_node(node1d); // AA tree         ; Expected: 1

    free_node(tree_a);
    free_node(tree_b);
    free_node(tree_c);
    free_node(node1d);

    // Exercice 84
    Graph* graphA = init_graph(4);

    graphA->edges[0][1] = true;
    graphA->edges[0][2] = true;
    graphA->edges[0][3] = true;
    graphA->edges[2][2] = true;
    graphA->edges[2][3] = true;
    graphA->edges[3][0] = true;

    int* resultA = dist_n(graphA, 0, 2); // 0, 2, 3
    int* resultB = dist_n(graphA, 0, 3); // 0, 1, 2, 3

    printf("Exercice 84 : the nodes at distance 2 from node 0 are : ");
    print_array_int(resultA, -1);

    printf("Exercice 84 : the nodes at distance 3 from node 0 are : ");
    print_array_int(resultB, -1);

    free(resultA);
    free(resultB);
    free_graph(graphA);

    print_newline;

    // Exercice 85
    double tab85a[] = { 1, 1 };        // (X-1)^2
    double tab85b[] = { 1, 1, 1, -1 }; // (X+1)(X-1)^3
    double tab85c[] = { 1, 2, 3 };     // (X-1)(X-2)(X-3)

    double* result85a = unitaire(tab85a, 2); // X^2 - 2X + 1
    double* result85b = unitaire(tab85b, 4); // X^4 - 2X^3 + 2X - 1
    double* result85c = unitaire(tab85c, 3); // X^3 - 6X^2 + 11X - 6

    printf("Exercice 85 : the polynomial is : ");
    print_array_double(result85a, 3);             // 1, -2, 1
    printf("Exercice 85 : the polynomial is : ");
    print_array_double(result85b, 5);             // -1, 2, 0, -2, 1
    printf("Exercice 85 : the polynomial is : ");
    print_array_double(result85c, 4);             // -6, 11, -6, 1

    free(result85a);
    free(result85b);
    free(result85c);

    print_newline;

    // Exercice 86
    char* tab86a_data[] = { "apple", "banana", "apple", "banana", "cherry" };
    char* tab86c_data[] = {
        "apple", "banana", "apple", "banana", "cherry",
        "apple", "banana", "cherry", "durian", "apple",
        "banana", "durian", "fig", "fig", "grape",
        "grape", "grape", "banana", "cherry", "durian"
    };

    double tab86c_values[20] = {
        2, 3,   4,   1, 5,
        6, 2,   7,  10, 8,
        4, 6, 3.5, 4.5, 2,
        4, 6,   5,   6, 4
    };

    Couple86** tab86a = malloc(5 * sizeof(Couple86*));
    for (int i = 0; i < 5; i += 1)
        tab86a[i] = create_couple86(tab86a_data[i], i + 1);

    Couple86** tab86b = malloc(5 * sizeof(Couple86*));
    for (int i = 0; i < 5; i += 1)
        tab86b[i] = create_couple86((char[]){ 'A' + i%2, '\0' }, (double) (i + 1) / 2);

    Couple86** tab86c = malloc(20 * sizeof(Couple86*));
    for (int i = 0; i < 20; i += 1)
        tab86c[i] = create_couple86(tab86c_data[i], tab86c_values[i]);

    Couple86** result86a = avggroupby(tab86a, 5);
    Couple86** result86b = avggroupby(tab86b, 5);
    Couple86** result86c = avggroupby(tab86c, 20);

    printf("Exercice 86 : the 'average group by' is :\n");
    print_couples86(result86a, 3);
    printf("Exercice 86 : the 'average group by' is :\n");
    print_couples86(result86b, 2);
    printf("Exercice 86 : the 'average group by' is :\n");
    print_couples86(result86c, 6);

    free_couples86(tab86a, 5);
    free_couples86(result86a, 3);
    free_couples86(tab86b, 5);
    free_couples86(result86b, 2);
    free_couples86(tab86c, 20);
    free_couples86(result86c, 6);

    print_newline;

    // Exercice 87
    char** strings87 = malloc(4 * sizeof(char*));
    strings87[0] = "123451234";
    strings87[1] = "aaatesttest";
    strings87[2] = "abcde";
    strings87[3] = "aaa";

    for (int i = 0; i < 4; i += 1)
    {
        IntCouple* result87 = facteurmax(strings87[i]);
        if (result87 == NULL) continue;

        printf("Exercice 87 : the 'max factor' of \"%s\" is located at : ", strings87[i]);
        printf("(%d, %d)\n", result87->a, result87->b);

        free(result87);
    }

    free(strings87);
    print_newline;

    // Exercice 88
    double** verticesA = malloc(2 * sizeof(double*));
    verticesA[0] = malloc(3 * sizeof(double));
    verticesA[1] = malloc(3 * sizeof(double));

    for (int i = 0, k = 1; i < 2; i += 1)
    {
        for (int j = 0; j < 3; j += 1)
        {
            verticesA[i][j] = k;
            k += 1;
        }
    }

    double** verticesB = malloc(2 * sizeof(double*));
    verticesB[0] = malloc(3 * sizeof(double));
    verticesB[1] = malloc(3 * sizeof(double));

    double verticesB_data[6] = { 9.1, 1.9, -5.8, -2.8, 0.3, 4.1 };
    for (int i = 0; i < 2; i += 1)
        for (int j = 0; j < 3; j += 1)
            verticesB[i][j] = verticesB_data[i * 3 + j];

    double* hyperplaneA = hyperplan(verticesA, 3);
    double* hyperplaneB = hyperplan(verticesB, 3);

    printf("Exercice 88 : the hyperplane cartesian equation is : ");
    print_array_double(hyperplaneA, 3); // 1, -2, 1
    printf("Exercice 88 : the hyperplane cartesian equation is : ");
    print_array_double(hyperplaneB, 3); // 1, -2.21092907..., 0.8447009444...

    free_matrix((int**) verticesA, 2);
    free(hyperplaneA);
    free_matrix((int**) verticesB, 2);
    free(hyperplaneB);

    print_newline;

    // Exercice 89
    char*** cardsA = make_cards(
        "SAS8SJS7D7D8D9DAC10C8CJCQC9CKH10H7HJHAH9H8D10S9DKC7SQCASKDQHQS10DJHK"
    );
    char* trumpA = "C";
    char* trumpB = "H";

    bool result89A = belote(trumpA, 0, cardsA);
    bool result89B = belote(trumpB, 3, cardsA);

    printf("Exercice 89 : The team with the player '%d' wins : %s\n", 0, str_of_bool(result89A));
    printf("Exercice 89 : The team with the player '%d' wins : %s\n", 3, str_of_bool(result89B));

    // Free the cards
    for (int i = 0; i < 8; i += 1)
        for (int j = 0; j < 4; j += 1)
            free(cardsA[i][j]);
    free_matrix((int**) cardsA, 8);

    return 0;
}

// Sources :
// Exercices originaux : http://jdreichert.fr/Enseignement/CPGE/MP2I/exercices.pdf
// PPCM ensembliste : https://fr.wikipedia.org/wiki/Plus_petit_commun_multiple
// Hash Table : https://en.wikipedia.org/wiki/Hash_table
// Binary Tree : https://en.wikipedia.org/wiki/Binary_tree
// Strahler number : https://en.wikipedia.org/wiki/Strahler_number
// AA-tree : https://en.wikipedia.org/wiki/AA_tree (from the Binary Tree page)
// Graphes : https://cahier-de-prepa.fr/mp*-corneille/download?id=254
// Wikipedia : https://en.wikipedia.org/wiki/Wikipedia 👀🙄
