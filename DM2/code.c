#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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
    int min = max;
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
int medianemax(int* tab, int size) {
    
    
    
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