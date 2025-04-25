#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


// Liste chainée :
struct value_noeud {double sum; int len;};
typedef struct value_noeud value_noeud;
struct noeud {char* key; value_noeud value; struct noeud* next;};
typedef struct noeud noeud;
struct l_c_i {noeud* head;};
typedef struct l_c_i ilc;

ilc* creer_ilc() {
    ilc* list = malloc(sizeof(ilc));
    list->head = NULL;
    return list;
}

void insert_ilc(ilc* l, char* key, double sum, int len) {
    noeud* head = malloc(sizeof(noeud));

    head->key = malloc((strlen(key) + 1)*sizeof(char));
    strcpy(head->key, key);

    value_noeud value = {.sum = sum, .len = len};
    head->value = value;

    head->next = l->head;
    l->head = head;
}

noeud* search_ilc(ilc* l, char* key) {
    noeud* current = l->head;
    while (current && strcmp(current->key, key) != 0) {
        current = current->next;
    }
    if (current) return current;
    return NULL;
}

// Table de Hachage :
typedef struct Hashtbl {int size; ilc** tab;} Hashtbl;

int hash(char* key, int size) {
    int h = 0;
    for (unsigned long int i=0; key[i] != '\0'; i++) {
        h = (h * 10) + key[i];
    }
    return abs(h % size);
}

Hashtbl* create_Hashtbl(int size) {
    Hashtbl* htbl = malloc(sizeof(Hashtbl));
    htbl->size = size;
    htbl->tab = malloc(size * sizeof(ilc*));
    for (int i=0; i<size; i++) {
        ilc* l = creer_ilc();
        htbl->tab[i] = l;
    }
    return htbl;
}

void add(Hashtbl* htbl, char* key, double sum, int len) {
    int index = hash(key, htbl->size);
    insert_ilc(htbl->tab[index], key, sum, len);
}

value_noeud search(Hashtbl* htbl, char* key) {
    int index = hash(key, htbl->size);
    noeud* node = search_ilc(htbl->tab[index], key);
    if (node) return node->value;
    return (value_noeud) {.sum = -1, .len = -1};
}

void replace(Hashtbl* htbl, char* key, int new_sum, int new_len) {
    int index = hash(key, htbl->size);
    noeud* node = search_ilc(htbl->tab[index], key);
    if (node) node->value = (value_noeud) {.sum = new_sum, .len = new_len};
    else {
        printf("élément non trouvé.\n");
        exit(1);
    }
}

void freeHashtbl(Hashtbl* htbl) {
    for (int i=0; i<htbl->size; i++) {
        noeud* current = htbl->tab[i]->head;
        while (current) {
            noeud* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        free(htbl->tab[i]);
    }
    free(htbl->tab);
    free(htbl);
}



// Exercice 80 NON
int pgcd(int a, int b) {
    if (b == 0) return a;
    return pgcd(b, a%b);
}

int ppcm(int a, int b) {
    return (a*b) / pgcd(a, b);
}

int aux_ppcm(int* tab, int n, int i) {
    if (i == n-1) return tab[i];
    if (i == n-2) return ppcm(tab[i], tab[i+1]);
    return ppcm(tab[i], aux_ppcm(tab, n, i+1));
}

int ppcm_ens(int* tab, int n) {
    if (n == 0) exit(1);
    return aux_ppcm(tab, n, 0);
}

void main1() {
    int tab[3] = {6, 15, 8};
    printf("%d\n", ppcm_ens(tab, 3)); // 120
}


// Exercice 81 NON (Il faut faire une optimisation avec table de hachage mais flemme)
bool aux_subsetsum(int* tab, int n, int v, int i, int sum) {
    if (i == n) return sum == v;
    return aux_subsetsum(tab, n, v, i+1, sum) || aux_subsetsum(tab, n, v, i+1, sum+tab[i]);
}

bool subsetsum(int* tab, int size, int v) {
    return aux_subsetsum(tab, size, v, 0, 0);
}

void main2() {
    int tab[5] = {8, 4, 7, 5, 2};
    printf("%d\n", subsetsum(tab, 5, 10)); // 1
}


// Exercice 82 OUI
int** selectfrom(int** sequence, int n, int* select, int taille_select) {
    int** rep = malloc(n * sizeof(int*));

    for (int i=0; i<n; i++) {
        rep[i] = malloc(taille_select * sizeof(int));
        for (int j=0; j<taille_select; j++) {
            rep[i][j] = sequence[i][select[j]];
        }
    }
    return rep;
}

void main3() {
    int select[4] = {2, 0, 3, 1};
    
    int** sequence = malloc(3 * sizeof(int*));
    for (int i=0; i<3; i++) {
        sequence[i] = malloc(4 * sizeof(int));
        for (int j=0; j<4; j++) {
            sequence[i][j] = i*4 + j + 1;
        }
    }

    printf("Séquence initale :\n");
    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
            printf("%d ", sequence[i][j]);
        }
        printf("\n");
    }

    int** rep = selectfrom(sequence, 3, select, 4);
    printf("Réponse :\n");
    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
            printf("%d ", rep[i][j]);
        }
        printf("\n");
    }

    for (int i=0; i<3; i++) free(sequence[i]);
    free(sequence);
    for (int i=0; i<3; i++) free(rep[i]);
    free(rep);
}


// Exercice 83 NON
struct noeud_arbre {int nb_children; struct noeud_arbre* children;};
typedef struct noeud_arbre noeud_arbre;

struct arbre {noeud_arbre* tete;};
typedef struct arbre arbre;

int strahler_aux(noeud_arbre noeud) {
    if (noeud.nb_children == 0) return 1;

    int max = -1;
    bool plus = false;
    for (int i=0; i < noeud.nb_children; i++) {
        int n = strahler_aux(noeud.children[i]);
        if (n > max) {plus = false; max = n;}
        else if (n == max) plus = true;
    }
    return plus ? max+1 : max;
}

int strahler(arbre arbre) {
    if (arbre.tete == NULL) return 0;
    return strahler_aux(*arbre.tete);
}

void main4() {
    noeud_arbre f1 = {.nb_children=0, .children = NULL};
    noeud_arbre f2 = {.nb_children=0, .children = NULL};
    noeud_arbre n1 = {.nb_children=2, .children = malloc(2*sizeof(noeud_arbre))};
    n1.children[0] = f1; n1.children[1] = f2;
    
    noeud_arbre f3 = {.nb_children=0, .children = NULL};
    noeud_arbre f4 = {.nb_children=0, .children = NULL};
    noeud_arbre n2 = {.nb_children=2, .children = malloc(2*sizeof(noeud_arbre))};
    n2.children[0] = f3; n2.children[1] = f4;

    noeud_arbre arb = {.nb_children = 2, .children = malloc(2*sizeof(noeud_arbre))};
    arb.children[0] = n1; arb.children[1] = n2;

    arbre a = {.tete = &arb};
    printf("%d\n", strahler(a)); // 3

    free(arb.children[0].children);
    free(arb.children[1].children);
    free(arb.children);
}


// Exercice 84 NON
struct noeud_graphe {int sommet; struct noeud_graphe* suivant;};
typedef struct noeud_graphe noeud_graphe;
struct l_adj {noeud_graphe* tete;};
typedef struct l_adj l_adj;
struct graphe {int nb_sommets; l_adj* listes_adj;};
typedef struct graphe graphe;

struct tableau {int* tab; int len;};
typedef struct tableau tableau;

void aux(graphe g, int n, int s, int etape, bool* tab) {
    if (etape == n) tab[s] = true;
    else {
        noeud_graphe* current = g.listes_adj[s].tete;
        while (current != NULL) {
            aux(g, n, current->sommet, etape+1, tab);
            current = current->suivant;
        }
    }
}

tableau dist_n(graphe g, int origine, int n) {
    bool* tab = malloc(g.nb_sommets * sizeof(bool));
    for (int i=0; i<g.nb_sommets; i++) tab[i] = false;
    
    aux(g, n, origine, 0, tab);
    int* tab_rep = malloc(g.nb_sommets * sizeof(int)); int len = 0;
    for (int i=0; i<g.nb_sommets; i++) {
        if (tab[i]) {
            tab_rep[len] = i;
            len++;
        }
    }
    tableau rep = {.tab = tab_rep, .len = len};
    free(tab);
    return rep;
}

void free_graphe(graphe g) {
    for (int s=0; s<g.nb_sommets; s++) {
        noeud_graphe* current = g.listes_adj[s].tete;
        while (current != NULL) {
            noeud_graphe* temp = current->suivant;
            free(current);
            current = temp;
        }
    }
    free(g.listes_adj);
}

void main5() {
    // CREATION DU GRAPHE
    graphe g;
    g.nb_sommets = 4;

    g.listes_adj = malloc(4 * sizeof(l_adj));
    for (int i = 0; i < 4; i++) {
        g.listes_adj[i].tete = NULL;
    }

    // A (0) -> B (1), C (2)
    noeud_graphe* n1 = malloc(sizeof(noeud_graphe));
    n1->sommet = 2;
    n1->suivant = NULL;

    noeud_graphe* n2 = malloc(sizeof(noeud_graphe));
    n2->sommet = 1;
    n2->suivant = n1;

    g.listes_adj[0].tete = n2;

    // B (1) -> C (2), D (3)
    noeud_graphe* n3 = malloc(sizeof(noeud_graphe));
    n3->sommet = 3;
    n3->suivant = NULL;

    noeud_graphe* n4 = malloc(sizeof(noeud_graphe));
    n4->sommet = 2;
    n4->suivant = n3;

    g.listes_adj[1].tete = n4;

    // C (2) -> D (3)
    noeud_graphe* n5 = malloc(sizeof(noeud_graphe));
    n5->sommet = 3;
    n5->suivant = NULL;

    g.listes_adj[2].tete = n5;

    // D (3) -> rien (NULL)
    g.listes_adj[3].tete = NULL;

    // TEST
    tableau rep = dist_n(g, 0, 2);
    for (int i=0; i<rep.len; i++) printf("%d ", rep.tab[i]); // 2 3
    printf("\n");
    free(rep.tab);
    free_graphe(g);
}


// Exercice 85 NON
double* mult(double* p1, int deg1, double* p2, int deg2) {
    double* rep = malloc((deg1+deg2+1) * sizeof(double));
    for (int i=0; i<deg1+deg2+1; i++) rep[i] = 0.0;

    for (int i=deg1; i>=0; i--) {
        for (int j=deg2; j>=0; j--) {
            rep[i+j] += p1[i] * p2[j];
        }
    }
    return rep;
}

double* unitaire(double* racines, int nb_racines) {
    if (nb_racines == 0) exit(1);
    double* rep = malloc((nb_racines+1) * sizeof(double));
    rep[0] = 1.0;
    int len = 1;
    for (int i=0; i<nb_racines; i++) {
        double temp[2] = {-racines[i], 1.0};
        double* pm = mult(rep, len-1, temp, 1);
        for (int k=0; k<len+1; k++) {
            rep[k] = pm[k];
        }
        len++;
        free(pm);
    }
    return rep;
}

void main6() {
    double racines[4] = {2.0, 1.0, 3.0, 8.0};
    double* polynome = unitaire(racines, 4);
    for (int i=0; i<=4; i++) printf("%f ", polynome[i]);
    printf("\n");
    free(polynome);
}


// Exercice 86 NON
struct couple_1 {char* s; double v;};
typedef struct couple_1 couple_1;

struct tableau_2 {int len; couple_1* tab;};
typedef struct tableau_2 tableau_2;

tableau_2 avggroupby(couple_1* tab, int size) {
    couple_1* rep = malloc(size * sizeof(couple_1)); int len = 0;

    Hashtbl* dict = create_Hashtbl(size);
    for (int i=0; i<size; i++) {
        value_noeud f = search(dict, tab[i].s);
        if (f.len == -1) add(dict, tab[i].s, tab[i].v, 1.0);
        else replace(dict, tab[i].s, f.sum+tab[i].v, f.len+1.0);
    }

    for (int i=0; i<dict->size; i++) {
        noeud* current = dict->tab[i]->head;
        while (current) {
            double m = current->value.sum / current->value.len;
            char* s = malloc((strlen(current->key)+1) * sizeof(char));
            strcpy(s, current->key);
            couple_1 couple = {.s = s, .v = m};
            rep[len] = couple;
            len++;

            current = current->next;
        }
    }

    freeHashtbl(dict);
    tableau_2 r = {.len = len, .tab = rep};
    return r;
}

void main7() {
    couple_1 data[20] = {
        {"apple", 2.0}, {"banana", 3.0}, {"apple", 4.0}, {"banana", 1.0},
        {"cherry", 5.0}, {"apple", 6.0}, {"banana", 2.0}, {"cherry", 7.0},
        {"durian", 10.0}, {"apple", 8.0}, {"banana", 4.0}, {"durian", 6.0},
        {"fig", 3.5}, {"fig", 4.5}, {"grape", 2.0}, {"grape", 4.0}, {"grape", 6.0},
        {"banana", 5.0}, {"cherry", 6.0}, {"durian", 4.0}
    };
    tableau_2 rep = avggroupby(data, 20);
    for (int i=0; i<rep.len; i++) {
        printf("(%s, %f) ", rep.tab[i].s, rep.tab[i].v);
        free(rep.tab[i].s);
    }
    printf("\n");
    free(rep.tab);
}


// Exercice 87 OUI
struct couple_2 {int a; int b;};
typedef struct couple_2 couple_2;

// Je garde la même implémentation que précedemment pour Hashtbl car non envie de réécrire l'interface. Ainsi l'argument len ne sert à rien dans la valeur d'un noeud.

couple_2 trouve(char* s, int n) {
    Hashtbl* htbl = create_Hashtbl(8);
    int len = strlen(s);
    couple_2 rep = {.a = -1, .b = -1};
    for (int i=0; i<len && i+n <= len; i++) {
        char* sequence = malloc((n+1) * sizeof(char)); sequence[0] = '\0';
        for (int j=0; j<n; j++) {
            sequence[j] = s[i+j];
            sequence[j+1] = '\0';
        }
        int deb = search(htbl, sequence).sum;
        if (deb == -1) {
            add(htbl, sequence, i, 0);
        } else {
            if (rep.a == -1 || deb < rep.a) {
                rep.a = deb; rep.b = i;
            }
        }
        free(sequence);
    }
    freeHashtbl(htbl);

    return rep;
}

couple_2 facteurmax(char* s) {
    int inf = 1; int sup = strlen(s);
    couple_2 rep = {.a = -1, .b = -1};
    while (inf <= sup) {
        int m = (inf+sup)/2;
        couple_2 temp = trouve(s, m);
        if (temp.a == -1 && temp.b == -1) sup = m-1;
        else {
            inf = m+1;
            rep = temp;
        }
    }
    if (rep.a == -1 && rep.b == -1) exit(1);
    return rep;
}

void main8() {
    char s[] = "aaatestliveblivetest";
    couple_2 rep = facteurmax(s);
    printf("(%d, %d)\n", rep.a, rep.b); // (3, 16)
}


// Exercice 88 OUI
double* gauss(double** A, double* B, int n) {
    double** matrice_aug = malloc(n * sizeof(double*));
    for (int i=0; i<n; i++) {
        matrice_aug[i] = malloc((n+1) * sizeof(double));
        for (int j=0; j<n; j++) matrice_aug[i][j] = A[i][j];
        matrice_aug[i][n] = B[i];
    }

    for (int i=0; i<n; i++) {
        // Pivot
        double pivot = matrice_aug[i][i];
        if (pivot == 0) {
            for (int j=i+1; j<n; j++) {
                if (matrice_aug[j][i] != 0) {
                    double* temp = matrice_aug[i];
                    matrice_aug[i] = matrice_aug[j];
                    matrice_aug[j] = temp;
                    pivot = matrice_aug[i][i];
                    break;
                }
            }
        }

        // Elimination
        for (int k=i; k<n+1; k++) matrice_aug[i][k] /= pivot;

        for (int j=i+1; j<n; j++) {
            double coeff = matrice_aug[j][i];
            for (int k=i; k<n+1; k++) {
                matrice_aug[j][k] -= coeff * matrice_aug[i][k];
            }
        }
    }
    // Résolution
    double* rep = malloc(n * sizeof(double));
    for (int i=n-1; i>=0; i--) {
        rep[i] = matrice_aug[i][n];
        for (int j=i+1; j<n; j++) {
            rep[i] -= matrice_aug[i][j] * rep[j];
        }
    }

    for (int i=0; i<n; i++) free(matrice_aug[i]);
    free(matrice_aug);
    return rep;
}

double* hyperplan(double** sequence, int n) {
    double* B = malloc((n-1) * sizeof(double));
    for (int i=0; i<n-1; i++) {
        B[i] = -sequence[i][0];
    }
    double** A = malloc((n-1) * sizeof(double*));
    for (int i=0; i<n-1; i++) {
        A[i] = malloc((n-1) * sizeof(double));
        for (int j=1; j<n; j++) {
            A[i][j-1] = sequence[i][j];
        }
    }

    double* g = gauss(A, B, n-1);
    double * rep = malloc(n * sizeof(double));
    rep[0] = 1.0;
    for (int i=1; i<n; i++) {
        rep[i] = g[i-1];
    }

    free(g);
    free(B);
    for (int i=0; i<n-1; i++) free(A[i]);
    free(A);
    return rep;
}

void main9() {
    double** sequence = malloc(2 * sizeof(double*));

    for (int i=0, k=1; i<2; i++) {
        sequence[i] = malloc(3 * sizeof(double));
        for (int j=0; j<3; j++) {
            sequence[i][j] = k;
            k++;
        }
    }

    double* hyperplan_sequence = hyperplan(sequence, 3);
    for (int i=0; i<3; i++) {
        printf("%f ", hyperplan_sequence[i]);
    }
    printf("\n");
    for (int i=0; i<2; i++) free(sequence[i]);
    free(sequence);
    free(hyperplan_sequence);
}


// Exercice 89


void main10() {
    
}


int main() {
    // main1();
    // main2();
    // main3();
    // main4();
    // main5();
    // main6();
    // main7();
    // main8();
    main9();
    // main10();
    return 0;
}
