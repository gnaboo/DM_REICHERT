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
int multpol(double* tab, double* tab2, int size, int size2)


int char_to_int(char caracter) {
    assert(caracter > )
    caracter
}

// Exo 27
int cesar(char* string, int a, int b) {
    assert(a != 0) // la fonction est bijective

    
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