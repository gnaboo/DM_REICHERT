#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

// Exo 20
int spitze(bool* tab, int size) {
    bool first = tab[0];
    for(int i = 1; i<size; i++) {
        if(tab[i] != first) return i-1;
    }
    return 1;
}

int position_of_last(bool* tab, int size, bool searched) {
    for(int i = 1; i<size-1; i++) {
        if(tab[size-i]==searched) return size-i;
    }
    return -1; // error
}

// Exo 21
void nul(bool* tab, int size) {
    int pos = position_of_last(tab, size, true);
    
}

// Exo 22
double modfloat(double a, double b) {
    if(b == 0) exit(133);
    if(b > a) return a; // fonctionnement similaire au a%b sur python
    int c = floor((a/b));
    return a - (c*b);
}

// Exo 23
int* minmax(int* tab, int size) {
    int max = tab[0];
    int min = max; // tab[0];
    for(int i = 0; i<size; i++) {
        if(tab[i] > max) max = tab[i];
        if(tab[i] < min) min = tab[i];
    }
    int* ret = malloc(sizeof(int)*2);
    ret[0] = min;
    ret[1] = max;
    return ret;
}

// Exo 24
int medianemax(int* tab, int size)


// Exo 25
int derive(double* tab, int size) {
    for(int i = 0; i<size; i++) {
        tab[i] = i*tab[i];
    }
}

// Exo 26
double* convolve(double* a, int size_a, double* b, int size_b) { // technically not a convolution but a cross-correlation
    int result_size = size_a + size_b - 1;
    double* result = malloc(result_size * sizeof(double));
    for(int i = 0; i < result_size; i++) {
        result[i] = 0.0;
    }

    for(int i = 0; i < size_a; i++) {
        for(int j = 0; j < size_b; j++) {
            result[i+j] += a[i]*b[j];
        }
    }
    return result;
}

int multpol(double* tab, double* tab2, int size, int size2) {
    return convolve(tab, size, tab2, size2);
}



bool is_lowercase(char car)
{
    if (car >= 'a' && car <= 'z')
        return true;
    return false;
}

bool is_uppercase(char car)
{
    if (car >= 'A' && car <= 'Z')
        return true;
    return false;
}

bool is_letter(char car)
{
    return (is_lowercase(car) || is_uppercase(car));
}

int char_to_int(char car)
{
    // on pose A = a (et par extension cela pour toutes les lettres)

    assert(is_letter(car))
    if(is_lowercase(car)) return car - 64
    if(is_uppercase(car)) return car - 96
}

// Exo 27
char* cesar(char* string, int a, int b) {
    assert(a != 0) // la fonction est bijective
    int size = (int) strlen(string);
    char* new_string = malloc(sizeof(char)*size); 

    for(int i = 0; i<size; i++) {
        new_string[i] = modfloat((a * char_to_int(string[i]) + b), 26);
    }
    return new_string;
}

// Exo 28
char* auguste(int nombre) {
    assert((nombre > 1) && (number < 3999));
    char* string = malloc(sizeof(char)*nombre);
    for(int i = 0; i<nombre; i++) {
        string[i] = "I"; // il ne s'agit pas de la notation 'standard' mais il s'agit néanmoins d'une notation correcte.
    }
    return string;
}

char* auguste_2(int nombre) {
    assert((nombre > 1) && (number < 3999));

    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 5, 4, 1};
    char* symboles[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "V", "IV", "I"};
    char* symb[13] = {};
    int size = 0;
    
    char* string = malloc(sizeof(char)*nombre);

    for(int i = 0; i<13; i++) {
        if(nombre > values[i]) {
            int val = (nombre - modfloat(nombre, values[i])) / values[i];
            symb[i] = val; // [*\tilde M] = [3]
            nombre -= val*values[i]; // ex: -3*1000 si MMM
            size += val; // ex: size += 3;
        }
    }

    char* string = malloc(sizeof(char), size);
    for(int i = 0; i<size; i++) {
        for(int y = 0; y<symb[i]; y++) {
            string[i] = symb[i];
        }
    }

    return string;
}



int main() {
    printf("----- Exercice 20 - spitze -----\n");
    bool tab[8] = {true, true, true, true, true, false, true, true};
    printf("%d\n", spitze(tab, 8));
    printf("%d\n", spitze(tab, 0));
    
    
    printf("----- Exercice 21 - nul -----\n");
    
    
    printf("----- Exercice 22 - modfloat -----\n");
    printf("%f\n", modfloat(12, 5));
    printf("%f\n", modfloat(18.2, 29));
    



    return 0;
}