#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Ex 80
int gcd(int a, int b)
{
    int pgcd = 1;
    for (int i = 1; i <= a && i <= b; i+=1)
    {
        if (a%i == 0 && b%i == 0) {pgcd = i;}
    }
    return pgcd;
}

int ppcm(int* tab, int size)
{
    if (size < 2) {return 0;}
    int p = tab[0];
    for (int i = 1; i < size; i += 1)
    {
        p = p * tab[i]/gcd(p, tab[i]);
    }
    return p;
}

//Ex 81
bool subsetsum(int* tab, int size, int x)
{
    if (size <= 0) {return (x == 0);}

    int* rst = tab + 1;
    return (subsetsum(rst, size -1, x)) || (subsetsum(rst, size -1, x-tab[0]));
}

//Ex 82
int* selectfrom(int** tab, int size1, int* ind, int size2)
{
    int* res = malloc(sizeof(int)*size2);
    for (int i = 0; i < size2; i += 1)
    {
        res[i] = tab[i][ind[i]];
    }
    return res;
}

//Ex 83
struct arbre {int noeud; struct arbre** enf; int nb};
typedef struct arbre arb;
arb* creerNoeud(int val, int nbe) {
    arb* nv = malloc(sizeof(arb));
    nv->noeud = val;
    nv->nb = nbe;
    if (nbe > 0) {
        nv->enf = malloc(nbe * sizeof(arb*));
    } else {
        nv->enf = NULL;
    }
    return nv;
}

int strahler(arb* a)
{
    int n = 0;
    if (a->nb == 0) {return 1;}
    int* c = malloc(sizeof(int)*a->nb);
    int max = 0;
    int cmax = 0;
    for (int i = 0; i < a->nb; i += 1)
    {
        c[i] = strahler(a->enf[i]);
        if (c[i] > max) 
        {
            max = c[i];
            cmax = 1;
        }
        else if (c[i] == max) {cmax += 1;}
    }
    free(c);
    return (cmax >= 2) ? max + 1 : max;
}



int main()
{
    //Ex 80
    int a[] = {1, 4, 10, 7, 12, 3};
    printf("ppcm: %d", ppcm(a, 6));

    //Ex 81
    printf("Validé avec validation: %d \n", subsetsum(a, 6, 17));
    printf("Nicht gut: %d", subsetsum(a, 6, 41));

    //Ex 82
    int un[] = {1, 2, 3};
    int deux[] = {4, 5, 6};
    int trois[] = {7, 8, 9};
    int* t[] = {un, deux, trois};
    int i[] = {0, 1, 2};
    int* s = selectfrom(t, 3, i, 3);

    printf("Résultat : ");
    for (int j = 0; j < 3; j+=1) {
        printf("%d; ", s[j]);
    }
    printf("\n");
    free(s);

    //Ex 83
    arb* n1 = creerNoeud(1, 3);
    arb* n2 = creerNoeud(2, 0);
    arb* n3 = creerNoeud(3, 2);
    arb* n4 = creerNoeud(4, 0);
    arb* n5 = creerNoeud(5, 0);
    arb* n6 = creerNoeud(6, 0);

    n1->enf[0] = n2;
    n1->enf[1] = n3;
    n1->enf[2] = n4;

    n3->enf[0] = n5;
    n3->enf[1] = n6;

    printf("Strahler : %d", strahler(n1));

    //Ex 84





    return 0;
}