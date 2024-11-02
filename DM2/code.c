#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

// Exo 20
int spitze(bool* tab, int size) {
    assert(size > 0);

    bool first = tab[0];
    for(int i = 1; i<size; i += 1) {
        if(tab[i] != first) return i-1;
    }
    return 1;
}

int position_of_last(bool* tab, int size, bool searched) {
    for(int i = 1; i<size-1; i += 1) {
        if(tab[size-i]==searched) return size-i;
    }
    return -1; // error
}

// Exo 21
void nul(bool* tab, int size) { // incompréhensible l'énoncé bordel
    int pos = position_of_last(tab, size, true);
    return pos;
}

// Exo 22
double c_abs(double a) {
    if(a < 0) return -a;
    return a;
}

double modfloat(double a, double b) {
    if(b == 0) exit(133);
    int sgn = b > 0 ? -1 : 1;

    if(c_abs(b) > c_abs(a)) return sgn*a; // fonctionnement similaire au a%b sur python

    int c = (int) floor(a/b);
    return a - (c*b);
}

// Exo 23
int* minmax(int* tab, int size) {
    assert(size > 0);

    int max = tab[0];
    int min = max; // tab[0];
    for(int i = 0; i<size; i += 1) {
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
    for(int i =1; i<size-1; i += 1) {
        tab[i - 1] = i * tab[i];
    }
}

// Exo 26
double* convolve(double* a, int size_a, double* b, int size_b) { // technically not a convolution but a cross-correlation
    int result_size = size_a + size_b - 1;
    double* result = malloc(result_size * sizeof(double));
    for(int i = 0; i < result_size; i += 1) {
        result[i] = 0.0;
    }

    for(int i = 0; i < size_a; i += 1) {
        for(int j = 0; j < size_b; j += 1) {
            result[i+j] += a[i]*b[j];
        }
    }
    return result;
}

int multpol(double* tab, double* tab2, int size, int size2) {
    return convolve(tab, size, tab2, size2); // multiplying a polynomial is equivalent to the convolution of the coefficiants
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
    if(is_lowercase(car)) return car - 64;
    if(is_uppercase(car)) return car - 96;
}



// Exo 27
char* cesar(char* string, int a, int b) {
    assert(a != 0); // la fonction est bijective
    int size = (int) strlen(string);
    char* new_string = malloc(sizeof(char)*size); 

    for(int i = 0; i<size; i += 1) {
        new_string[i] = modfloat((a * char_to_int(string[i]) + b), 26);
    }
    return new_string;
}



// Exo 28
char* auguste(int nombre) {
    assert((nombre > 1) && (number < 3999));
    char* string = malloc(sizeof(char)*nombre + 1);
    for(int i = 0; i<nombre; i += 1) {
        string[i] = "I"; // il ne s'agit pas de la notation 'standard' mais il s'agit néanmoins d'une notation correcte.
    }
    string[nombre + 1] = '\0';
    return string;
}

char* auguste_2(int nombre) {
    assert((nombre >= 1) && (nombre <= 3999));

    int value[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* result = malloc(sizeof(char) * 20);
    for(int i = 0; i<sizeof(char)*19; i += 1) { result[i] = '\0'; }

    for(int i = 0; i<13; i += 1) {
        while(nombre >= value[i]) {
            strcat(result, symbols[i]);
            nombre -= value[i];
        }
    }
    //strcat(result, '\0'); with `strcat()`, the resulting string in dest is always null-terminated. source: https://linux.die.net/man/3/strcat

    return result;
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