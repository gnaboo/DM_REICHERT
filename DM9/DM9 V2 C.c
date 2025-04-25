#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//Exercice 80 : Écrire une fonction ppcm_ens prenant en argument une séquence 
//d’entiers naturels non nuls
//et retournant le PPCM global de cette séquence.

int pgcd (int a, int b)
{
    if (b==0) return a;
    return pgcd(b,a%b);
}

int ppcm (int a, int b)
{
    return (a*b)/pgcd(a,b);
}
int ppcm_ens(int* tab, int n)
{
    int ppcmact=ppcm(tab[0],tab[1]);
    for (int i=2;i<n;i+=1)
        ppcmact=ppcm(ppcmact,tab[i]);
    return ppcmact;
}

//Exercice 81 : Écrire une fonction subsetsum prenant en argument 
//une séquence d’entiers ainsi qu’un autre entier et déterminant si 
//celui-ci peut s’écrire comme la somme d’une sous-séquence de la séquence.

bool subsetsum (int* seq, int n, int x)
{
    
    int min_somme=0;
    int max_somme=0;
    for (int i=0;i<n; i+=1)
    {
        if (seq[i]<0) min_somme+=seq[i];
        else max_somme+=seq[i];
    }
    int decalage=-min_somme;
    int plage=max_somme+decalage + 1;
    
    bool**tab=malloc((n+1)*sizeof(bool*));
    for (int i=0; i<n+1; i+=1) 
    {
        tab[i]=malloc((plage)*sizeof(bool));
    }
    for (int i = 0; i < n+1; i+=1) 
    {
        for (int j = 0; j < plage; j+=1) tab[i][j] = false;
    }
    tab[0][decalage] = true;
    for (int i=1; i<n+1; i+=1)
    { 
    
        for (int j=0; j<plage;j+=1)
        {
            if(tab[i-1][j])
            {
                tab[i][j]=true;
                int pch_elt=j+seq[i - 1];
                if (pch_elt>=0 && pch_elt<plage) tab[i][pch_elt]=true;
            }
        }
    }
    bool res=false;
    if (x + decalage >= 0 && x + decalage < plage) res = tab[n][x + decalage];
    for (int i=0; i<n+1; i+=1) free (tab[i]);
    free (tab);
    return res;
    
}

//Exercice 82 : Écrire une fonction selectfrom prenant en argument une séquence 
//de tableaux (en C : d’entiers) tous de même taille ainsi qu’une séquence 
//supplémentaire d’entiers entre zéro et la taille du tableau
//moins un (pas forcément monotone, mais on peut supposer qu’il n’y a pas 
//de répétitions) et retournant une séquence formée des tableaux précédents 
//dans le même ordre au sein de la séquence mais dont les éléments
//sont ceux aux indices précisés dans la séquence en respectant l’ordre d’énonciation.

int** selectfrom (int taille_seq, int taille_tab, int seq[][taille_tab],int*seq_entiers, int taille_seq_entiers)
{
    int**tab=malloc(taille_seq*sizeof(int*));
    for (int i = 0; i<taille_seq; i+=1)
    {
        tab[i]=malloc(taille_seq_entiers*sizeof(int));
    }
    for (int i=0; i<taille_seq; i+=1)
    {
        for (int j=0;j<taille_seq_entiers;j+=1)
        {
            tab[i][j]=seq[i][seq_entiers[j]];
        }
    }
    return tab;
}

//Exercice 83 : Écrire une fonction strahler prenant en argument un arbre (type sans 
//étiquette à définir,arité quelconque) et retournant son nombre de Strahler

struct arbre {int nb_enfants; struct arbre** enfants;};
typedef struct arbre arb;

arb* creer_arbre (int nb_enfant)
{
    
    arb** tab=malloc(nb_enfant*sizeof(arb*));
    arb* a =malloc(sizeof(arb));
    a->nb_enfants=nb_enfant;
    a->enfants=tab;
    return a;
}
    
    
    

int strahler (arb* a)
{
    if (a->nb_enfants ==0) return 1;
    else
    {
        int maxi=0;
        int compteur=0;
        for (int i=0; i<a->nb_enfants; i+=1)
        {
            int stalfos=strahler (a->enfants[i]);
            if (stalfos>maxi)
            {
                maxi=stalfos;
                compteur=1;
            }
            else if (stalfos==maxi) compteur+=1;
        }
        if (compteur>=2) return maxi+1;
        else return maxi;
    }
}

//Exercice 84 : Écrire une fonction dist_n prenant en argument un graphe orienté 
//(représentation au choix), un sommet du graphe et un entier naturel et retournant 
//la séquence des sommets qui sont la destination d’au moins un chemin d’origine le 
//sommet en argument et de longueur exactement l’entier en argument

struct graphe_orienté {int nb_sommets; int**mat_adj;};
typedef struct graphe_orienté go;

int**allouer_matrice_carree(int taille)
{
    int**new_mat=malloc(taille*sizeof(int*));
    for (int i=0;i<taille;i+=1) 
    {
        new_mat[i]=malloc(taille*sizeof(int));
        for (int j=0;j<taille;j+=1) new_mat[i][j]=0;
    }
    return new_mat;
}

void liberer_matrice(int** matrice, int taille)
{
    for (int i = 0; i<taille; i+=1)
    {
        free(matrice[i]);
    }
    free(matrice);
}

int** mult_mat_carre (int** A, int** B, int taille)
{
    int **new_mat=allouer_matrice_carree(taille);
    for (int i=0; i<taille; i+=1) 
    {
        for (int j=0;j<taille;j+=1)
        {
            new_mat[i][j]=0;
            for (int k=0;k<taille;k+=1)
            {
                new_mat[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    return new_mat;
}

int** puissance_matrice (int**matrice, int taille, int expo)
{
    int**res=allouer_matrice_carree(taille);
    for(int i=0;i<taille;i+=1) res[i][i]=1;
    
    int** base = allouer_matrice_carree(taille);
    for (int i = 0; i < taille; i+=1)
        for (int j = 0; j < taille; j+=1)
            base[i][j] = matrice[i][j];
    while(expo>0)
    {
        if(expo%2==1)
        {
            int** temp = mult_mat_carre(res, base, taille);
            liberer_matrice(res, taille);
            res = temp;
        }
        int** temp = mult_mat_carre(base, base, taille);
        liberer_matrice(base, taille);
        base = temp;
        expo /= 2;
    }
    liberer_matrice(base, taille);
    return res;
}


int*dist_n (go* g, int s, int n,int* t)
{
    int* temp = malloc(g->nb_sommets*sizeof(int));
    int indice=0;
    int taille=g->nb_sommets;
    
    int**mat_adj_pown=puissance_matrice(g->mat_adj,taille,n);
    for (int i=0; i<g->nb_sommets;i+=1)
        if (mat_adj_pown[s][i]>=1) 
        {
            temp[indice]=i;
            indice+=1;
        }
    int* seq=malloc(indice*sizeof(int));
    for (int i=0;i<indice;i+=1) seq[i]=temp[i];
    liberer_matrice(mat_adj_pown, taille);
    *t=indice;
    free(temp);
    return seq;
    
    
}

//Exercice 85 : Écrire une fonction unitaire prenant en argument une 
//séquence de flottants et retournant une séquence de flottants 
//représentant un polynôme unitaire ayant exactement les éléments de 
//la séquence en argument pour racine. Le premier élément de la séquence 
//retournée correspondra au coefficient constant.

double* unitaire (double* seq, int taille)
{
    double* poly=malloc((taille+1)*sizeof(double));
    for (int i=0;i<taille+1;i+=1) poly[i]=0.0;
    poly[0]=1.0;
    int degre=0;
    for (int i =0;i<taille;i+=1)
    {
        for (int j=degre;j>=0;j-=1)
        {
            poly[j+1]+=poly[j];
            poly[j]*=-seq[i];
        }
        degre+=1;
    }
    return poly;
}

//Exercice 86 : Écrire une fonction avggroupby prenant en argument une 
//séquence de couples formés chacun par une chaîne de caractères et un nombre 
//(entier ou flottant au choix, utiliser struct en C) et retournant une 
//séquence de couples dont les premiers éléments sont toutes les chaînes de 
//caractères rencontrées sans répétition et les deuxièmes éléments sont les 
//moyennes (forcément en tant que flottants) des valeurs associées
//à la chaîne correspondante.

struct couple {char* c;double n;};
typedef struct couple couple;

couple* avggroupby (couple* seq, int taille, int*chaines_dif)
{
    int* occ_chaine = malloc(taille*sizeof(int));
    for (int i=0; i<taille; i+=1) occ_chaine[i]=0;
    
    couple* res=malloc(taille*sizeof(couple));
    
    for (int i=0; i<taille; i+=1)
    {
        int trouvee=0;
        for(int j=0; j<*chaines_dif; j+=1)
        {
            if (!strcmp(seq[i].c,res[j].c)) 
            {
                occ_chaine[j]+=1;
                res[j].n+=seq[i].n;
                trouvee=1;
                break;
            }
        }
        if (!trouvee)
        {
            res[*chaines_dif].c=strdup(seq[i].c);
            res[*chaines_dif].n=seq[i].n;
            occ_chaine[*chaines_dif]+=1;
            *chaines_dif+=1;
        }
    }
    for (int i=0;i<*chaines_dif;i+=1)
    {
        res[i].n/=occ_chaine[i];
    }
    free(occ_chaine);
    return res;
}

int main()
{
    //Exercice 80
    int tab[4]={12,4,6,24};
    int taille=4;
    printf("%d",ppcm_ens(tab,taille)); //Doit retourner 24
    
    //Exercice 81
    int seq[3]={3,5,7};
    int taille2=3;
    printf("\n%d",subsetsum(seq,taille2,8)); //Doit retourner true
    printf("\n%d",subsetsum(seq,taille2,4)); //Doit retourner false
    int seq2[5] = {3, -2, 7, -5, 1};
    int taille3=5;
    int cible = -4;
    printf("\n%d\n",subsetsum(seq2,taille3,cible)); //Doit retourner true
    
    //Exercice 82
    int tableaux[3][4] = {{10, 20, 30, 40},{50, 60, 70, 80},{90, 100, 110, 120}};
    int taille_seq = 3; 
    int taille_tab=4;
    int indices[2] = {2, 0};
    int taille_seq_entiers=2;
    int** tableau=selectfrom(taille_seq,taille_tab,tableaux,indices,taille_seq_entiers);
    for (int i=0;i<taille_seq;i+=1)
    {
        for (int j=0;j<taille_seq_entiers;j+=1)
        {
            printf("%d ",tableau[i][j]);
        }
        free(tableau[i]);
    }
    free(tableau);
    
    //Exercice 83
    arb* D = creer_arbre(0);
    arb* C = creer_arbre(1);
    arb* B = creer_arbre(0);
    arb* A = creer_arbre(0);
    arb* R = creer_arbre(3);
    C->enfants[0]=D;
    R->enfants[0]=A;
    R->enfants[1]=B;
    R->enfants[2]=C;
    printf("\nIndice de Strahler : %d\n",strahler(R)); //Doit retourner 2
    free(A->enfants);
    free(A);
    free(B->enfants);
    free(B);
    free(C->enfants);
    free(C);
    free(D->enfants);
    free(D);
    free(R->enfants);
    free(R);
    arb* a = creer_arbre(2);
    a->enfants[0] = creer_arbre(0);
    a->enfants[1] = creer_arbre(0);
    printf("\nIndice de Strahler : %d\n", strahler(a)); // Résultat attendu : 2
    free(a->enfants[0]->enfants);
    free(a->enfants[1]->enfants);
    free(a->enfants[0]);
    free(a->enfants[1]);
    free(a->enfants);
    free(a);
    
    //Exercice 84
    go graphe;
    graphe.nb_sommets=4;
    graphe.mat_adj= allouer_matrice_carree(graphe.nb_sommets);

    // Graphe orienté
    graphe.mat_adj[0][1] = 1;
    graphe.mat_adj[0][2] = 1;
    graphe.mat_adj[1][2] = 1;
    graphe.mat_adj[2][3] = 1;
    graphe.mat_adj[3][0] = 1;
    int t=0;
    int* result = dist_n(&graphe, 0, 2,&t);

    printf("Sommets atteignables depuis le sommet 0 en 2 étapes :\n");
    for (int i = 0; i < t; i+=1) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
    liberer_matrice(graphe.mat_adj, graphe.nb_sommets);

    //Exercice 85
    double seq[4]={1,2,3,4};
    int taille=4;
    double*poly=unitaire(seq,taille);
    for (int i=0;i<taille+1;i+=1)
        {
            printf("poly[%f]\n",poly[i]);
        }
    free(poly);
    
    //Exercice 86
    couple a={"pomme",2.0};
    couple b={"banane",3.0};
    couple c={"pomme",4.0};
    couple d={"banane",5.0};
    couple e={"pomme",1.0};
    couple seq2[5]={a,b,c,d,e};
    int chaines_dif=0;
    couple* res=avggroupby(seq2,5,&chaines_dif);
    for(int i =0;i<chaines_dif;i+=1)
    {
        printf("La moyenne des valeurs associées à %s est %f. ",res[i].c, res[i].n);
        free(res[i].c);
    }


    return 0;
    
}