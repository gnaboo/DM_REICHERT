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
    int start = size < 0 ? 1 : 0;
    if (size < 0) size = array[0];

    for (int i = start; i < size + start; i += 1) printf("%d ", array[i]);
    printf("\n");
}

void print_array_float(double* array, int size)
{
    int start = size < 0 ? 1 : 0;
    if (size < 0) size = array[0];

    for (int i = start; i < size + start; i += 1) printf("%g ", array[i]);
    printf("\n");
}

void print_polynomial(double* P, int size) {
    int start = size < 0 ? 1 : 0;
    if (size < 0) size = (int) P[0];

    bool first = true;

    for (int i = start; i < size + start; i++) if (P[i] != 0) {
        printf("%s%s%g", first ? "" : " ", P[i] < 0 ? "- " : (first ? "" : "+ "), fabs(P[i]));
        first = false;

        if (i == 1) printf("*X");
        if (i > 1) printf("*X^%d", i);
    }

    if (first) printf("0");
}

void print_79(double* A, int sizeA, double* B, int sizeB, double* Q)
{
    printf("Exercice 79 : ");
    print_polynomial(A, sizeA);
    printf(" = (");
    print_polynomial(B, sizeB);
    printf(") * (");
    print_polynomial(Q, sizeA - sizeB + 1);
    printf(") + R\n");
}

void minMaxPairwise(int arr[], int n, int *min, int *max) {
    int i = 0;

    if (n % 2 == 0) {
        bool isMin = arr[0] < arr[1];

        *min = isMin ? arr[0] : arr[1];
        *max = isMin ? arr[1] : arr[0];

        i = 2;
    } else {
        *min = arr[0];
        *max = arr[0];

        i = 1;
    }

    while (i < n - 1) {
        if (arr[i] < arr[i + 1]) {
            if (arr[i] < *min) *min = arr[i];
            if (arr[i + 1] > *max) *max = arr[i + 1];
        } else {
            if (arr[i + 1] < *min) *min = arr[i + 1];
            if (arr[i] > *max) *max = arr[i];
        }

        i += 2;
    }
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

    printf("\n");
}

// Functions
// Exercice 70 :
bool cycle(int* tab, int size)
{
    // Trivial case
    if (size == 0) return true;

    // Copy the array (avoid "NPMA")
    int* t = malloc(size * sizeof(int));
    for (int i = 0; i < size; i += 1) t[i] = tab[i];

    // Check if there is a cycle
    int i = 0;
    int count = 0;

    while (count < size && t[i] != -1 && t[i] < size && t[i] >= 0)
    {
        int next = t[i];

        t[i] = -1;
        i = next;

        count += 1;
    }

    free(t);

    return count == size;
}

// Exercice 71 :
bool idem(int* tab, int size)
{
    // Trivial case
    if (size == 0) return true;

    // Initialize the answer
    int* t = malloc(size * sizeof(int));
    for (int i = 0; i < size; i += 1) t[i] = tab[i];

    // Apply the permutation
    for (int i = 1; i < size; i += 1)
    {
        int* temp = malloc(size * sizeof(int));

        for (int j = 0; j < size; j += 1) temp[j] = tab[t[j]];
        for (int j = 0; j < size; j += 1) t[j] = temp[j];

        free(temp);
    }

    bool res = true;

    for (int i = 0; i < size; i += 1)
    {
        if (t[i] != i)
        {
            res = false;
            break;
        }
    }

    free(t);
    return res;
}

// Exercice 72 :
bool is_space(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

char* empty_string()
{
    char* buffer = malloc(1 * sizeof(char));
    buffer[0] = '\0';
    return buffer;
}

char* elaguer (char* buffer)
{
    int len = strlen(buffer);
    if (len == 0) return empty_string();

    // create a new iterator to store the new string
    // (chars will be stored as integers)
    Iterator* iterator = create_iterator(buffer[0]);
    bool was_space = is_space(buffer[0]);

    int new_len = 1;

    for (int i = 1; i < len; i += 1)
    {
        // Exchange line breaks and tabs with spaces
        if (is_space(buffer[i]))
        {
            if (!was_space)
            {
                add_iterator(iterator, 32);
                was_space = true;
                new_len += 1;
            }
        }
        else
        {
            add_iterator(iterator, buffer[i]);
            was_space = false;
            new_len += 1;
        }
    }

    // trim the string
    if (was_space) new_len -= 1;

    bool trimStart = iterator->value == 32; // type-friendly
    new_len -= trimStart ? 1 : 0;

    if (new_len < 1) {
        free_iterator(iterator);
        return empty_string();
    }

    // Return the new string
    int i = 0;
    char* new_buffer = malloc((new_len + 1) * sizeof(char));

    Iterator* it = trimStart ? iterator->next : iterator;

    while (it)
    {
        new_buffer[i] = it->value;
        i += 1;

        it = it->next;
    }

    free_iterator(iterator);

    new_buffer[new_len] = '\0';
    return new_buffer;
}

// Exercice 73 :
int nombrediviseurs(int n)
{
    if (n < 1) return 0; // n must be a postive non-zero integer
    if (n == 1) return 1;

    int sqrt_n = sqrt(n); // check if we can use this function
    int count = sqrt_n * sqrt_n == n ? -1 : 0;

    for (int i = 1; i <= sqrt_n; i += 1)
        if (n % i == 0) count += 2;

    return count;
}

// Exercice 74 :
// I could just have used a single size parameter... but, nevermind, I'll keep it this way
int maxintersect(int* start, int startSize, int* end, int endSize)
{
    // Filter invalid inputs
    if (startSize != endSize)
    {
        printf("Invalid input\n");
        exit(1);
    }

    if (startSize < 2) return 0;

    // Let's do the job :D
    int i = 0;
    int j = 0;

    int maxOverlap = 0;
    int currentOverlap = 0;

    while (i < startSize && j < endSize)
    {
        if (start[i] < end[j])
        {
            currentOverlap += 1;
            i += 1;
        }
        else
        {
            currentOverlap -= 1;
            j += 1;
        }

        if (currentOverlap > maxOverlap)
            maxOverlap = currentOverlap;
    }

    return maxOverlap;
}

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
        if (i == j*2) j *= 2;                        // v1: if (i >> 1 == j) j <<= 1;
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

    while (n >= i)      // hmpf, using a `for` loop would have been better >.<
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
int noteToIndex(char* note) // input ex: "sol3", "mib1", "fad2"
{
    int len = strlen(note);

    char* notes[] = { "do", "dod", "ré", "réd", "mi", "fa", "fad", "sol", "sold", "la", "lad", "si" };
    char* bemols[] = { "do", "réb", "ré", "mib", "mi", "fa", "solb", "sol", "lab", "la", "sib", "si" };

    // set the octave (ex: 3, 1, 2)
    int octave = note[len - 1] - '0';
    // set the note name (ex: "sol", "mib", "fad")
    char* noteName = malloc(len * sizeof(char));

    for (int i = 0; i < len - 1; i += 1) noteName[i] = note[i];
    noteName[len - 1] = '\0';

    int noteIndex = 0;

    for (int i = 0; i < 12; i += 1)
    {
        if (strcmp(noteName, notes[i]) == 0 || strcmp(noteName, bemols[i]) == 0)
        {
            noteIndex = i;
            break;
        }
    }

    free(noteName);
    return octave * 12 + noteIndex;
}

int tessiture(char** tab, int size)
{
    // Always check the trivial cases :O
    if (size < 2) return 0;

    // Convert the notes to indexes
    int* notes = malloc(size * sizeof(int));
    for (int i = 0; i < size; i += 1) notes[i] = noteToIndex(tab[i]);

    // Get the min and max values
    int min = notes[0];
    int max = notes[0];

    minMaxPairwise(notes, size, &min, &max);
    free(notes);

    return max - min; // hehehe, I used the easy way :D
}

// Exercice 79 :
double* diveucl(double* A, int sizeA, double* B, int sizeB)
{
    // Check if the inputs are valid :
    // (sizeA >= sizeB >= 1) <=> (deg(A) >= deg(B) >= 0)
    if (sizeA < sizeB || sizeA < 1 || sizeB < 1 || A[sizeA - 1] == 0 || B[sizeB - 1] == 0)
    {
        printf("Invalid input\n");
        return NULL;
    }

    // Copy A into P
    double* P = malloc(sizeA * sizeof(double));
    for (int i = 0; i < sizeA; i += 1) P[i] = A[i];

    // We're searching for Q such that A = BQ + R (R doesn't matter here)
    double* Q = malloc((sizeA - sizeB + 1) * sizeof(double));
    int i = sizeA - sizeB;

    while (sizeA >= sizeB)
    {
        double q = P[sizeA - 1] / B[sizeB - 1];
        int d = sizeA - sizeB;

        // P -= q * B * X^d
        for (int j = 0; j < sizeB; j += 1)
            P[j + d] -= q * B[j];

        Q[i] = q;

        sizeA -= 1;
        i -= 1;
    }

    // Free and return the answer
    free(P);
    return Q;
}

// Tests
int main()
{
    // Exercice 70
    int t70a[] = {2, 0, 3, 1};
    int t70b[] = {1, 0, 3, 2};

    printf("Exercice 70 : %s\n", cycle(t70a, 4) ? "true" : "false"); // true
    printf("Exercice 70 : %s\n", cycle(t70b, 4) ? "true" : "false"); // false

    printf("\n");

    // Exercice 71
    int t71a[] = {2, 0, 3, 1};
    int t71b[] = {1, 2, 3, 0};
    int t71c[] = {1, 2, 2, 0};


    printf("Exercice 71 : %s\n", idem(t71a, 4) ? "true" : "false"); // true
    printf("Exercice 71 : %s\n", idem(t71b, 4) ? "true" : "false"); // true
    printf("Exercice 71 : %s\n", idem(t71c, 4) ? "true" : "false"); // false

    printf("\n");

    // Exercice 72
    char* ex72a = "Hello\n  World !";
    char* ex72b = "   Ligne1    \r\n    Ligne2   avec   espaces   \n  \t  Ligne3\r   Ligne4    \n   Beaucoup     d'espaces ici   ";
    char* ex72c = "";
    char* ex72d = " .";
    char* ex72e = ". ";
    char* ex72f = " . ";
    char* ex72g = "   \n    \r    \t      ";

    char* ex72a_o = elaguer(ex72a); // "Hello World !"
    char* ex72b_o = elaguer(ex72b); // "Ligne1 Ligne2 avec espaces Ligne3 Ligne4 Beaucoup d'espaces ici"
    char* ex72c_o = elaguer(ex72c); // ""
    char* ex72d_o = elaguer(ex72d); // "."
    char* ex72e_o = elaguer(ex72e); // "."
    char* ex72f_o = elaguer(ex72f); // "."
    char* ex72g_o = elaguer(ex72g); // ""

    printf("Exercice 72 : \"%s\"\n", ex72a_o); free(ex72a_o);
    printf("Exercice 72 : \"%s\"\n", ex72b_o); free(ex72b_o);
    printf("Exercice 72 : \"%s\"\n", ex72c_o); free(ex72c_o);
    printf("Exercice 72 : \"%s\"\n", ex72d_o); free(ex72d_o);
    printf("Exercice 72 : \"%s\"\n", ex72e_o); free(ex72e_o);
    printf("Exercice 72 : \"%s\"\n", ex72f_o); free(ex72f_o);
    printf("Exercice 72 : \"%s\"\n", ex72g_o); free(ex72g_o);

    printf("\n");

    // Exercice 73
    int ex73[6] = { 0, 1, 25, 3, 6, 42 };

    for (int i = 0; i < 6; i += 1)
        printf("Exercice 73 : %d\n", nombrediviseurs(ex73[i]));

    printf("\n");

    // Exercice 74
    int start74[] = {1, 2, 3, 4};  // Trié par début croissant
    int end74[] = {5, 6, 7, 8};    // Trié par fin croissante
    int n = 4;

    int ex74 = maxintersect(start74, n, end74, n);
    printf("Exercice 74 : %d\n\n", ex74);

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

    // 2, 24, 249 (j'ai dénombré à la main les zéros...)
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
    char* ex78a[] = { "do3", "mib1", "fad2", "lab4" };
    char* ex78b[] = { "do3", "mib1", "fad2", "lab3", "si4" };

    printf("Exercice 78 : %d\n", tessiture(ex78a, 4));
    printf("Exercice 78 : %d\n", tessiture(ex78b, 5));

    printf("\n");

    // Exercice 79
    double ex79a_A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    double ex79a_B[] = { .5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5 };
    double ex79b_A[] = { 5, 1, 3, 2 };
    double ex79b_B[] = { 1, 1.1 };
    double ex79c_A[] = { 1, 0, -1, 1 };
    double ex79c_B[] = { 0, 0, 1 };
    double ex79d_A[] = { 0, -2, 3, -1, -1, 1 };
    double ex79d_B[] = { 1, -1, 1 };

    double* ex79a = diveucl(ex79a_A, 9, ex79a_B, 9); // 2
    print_79(ex79a_A, 9, ex79a_B, 9, ex79a);
    print_array_float(ex79a, 1); free(ex79a);

    double* ex79b = diveucl(ex79b_A, 4, ex79b_B, 2); // -0.0676183..., 1.07438..., 1.81818...
    print_79(ex79b_A, 4, ex79b_B, 2, ex79b);
    print_array_float(ex79b, 3); free(ex79b);

    double* ex79c = diveucl(ex79c_A, 4, ex79c_B, 3); // -1, 1
    print_79(ex79c_A, 4, ex79c_B, 3, ex79c);
    print_array_float(ex79c, 2); free(ex79c);

    double* ex79d = diveucl(ex79d_A, 6, ex79d_B, 3); // 1, -2, 0, 1
    print_79(ex79d_A, 6, ex79d_B, 3, ex79d);
    print_array_float(ex79d, 4); free(ex79d);

    return 0;
}

// Sources :
// Fonctionnement de `elaguer` : inspiré d'un code en JS pour un projet perso xD
// Suite de Prouhet-Thue-Morse : https://fr.wikipedia.org/wiki/Suite_de_Prouhet-Thue-Morse
// Formule de Legendre (valuation p-adique de la factorielle) : https://fr.wikipedia.org/wiki/Formule_de_Legendre
// Fonctionnement de `tessiture` : Olympe et Gabriel
// minMaxPairwise: Astuce de Dany
