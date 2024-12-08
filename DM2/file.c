#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Ex 20:
int spitze(bool *t, int size)
{
    int nb=1;
    int i=1;
    while (i<size && t[i]==t[0])
    {
        nb+=1;
        i+=1;
    }
    return nb;
}

Ex 21:
bool nul(bool *t, int size)
{
    int tr=0;
    int fa=0;
    int last_tr= 0;
    for (int i=0; i<size; i+=1)
    {
        if (t[i]) {last_tr=i;}
    }
    
    int j=0;
    while (j<last_tr)
    {
        j+=1;
        if (t[j]) {tr+=1;}
        else {fa +=1;}
        
        if (fa>tr) {return false;}
    }
    return true;
}

Ex 22:
double modfloat(double a, double b)
{
    int quotient=(int)(a/b);
    double reste=a-quotient*b;
    if (reste<0) {reste+=b;}
    return reste;
}

Ex 23:
struct minMax{
    int min;
    int max;
};
typedef struct minMax mM;
mM result;

void minmax(int *t, int size)
{
    result.min=t[0];
    result.max=t[0];
    for (int i=1; i<size; i+=1)
    {
        if (t[i]<result.min) {result.min=t[i];}
        else if (t[i]>result.max) {result.max=t[i];}
    }
}

Ex 24:
int medianemax(int *t, int size)
{
    int max=t[0];
    for (int i=1; i<size;i+=1)
    {
        if (t[i]>max) {max=t[i];}
    }
    
    int *indices=malloc(size*sizeof(int));
    int count=0;
    for (int i=0; i<size; i+=1)
    {
        if (t[i]==max)
        {
            indices[count]=i;
            count+=1;
        }
    }
    
    int mediane;
    if (count%2 == 0) {
        mediane=indices[(count/2)-1];
    }
    else {     
        mediane=indices[count/2];
    }
    free(indices);
    return mediane;
}

Ex 25:
void derive(double *t, int size)
{
    for (int i=1; i<size; i+=1)
    {
        t[i-1]=t[i]*i;
    }
    t[size-1]=0;
}

Ex 26:
double* multpol(double *t1, int size1, double *t2, int size2)
{
    double *p= malloc((size1+size2-1) * sizeof(double));
    for (int i=0; i<size1+size2-1; i+=1)
    {
        p[i]=0;
    }
    for (int i=0; i<size1; i+=1)
    {
        for (int j=0; j<size2; j+=1)
        {
            p[i+j]+=t1[i]*t2[j];
        }
    }
    return p;
}

Ex 28:
char* auguste(int a)
{
	char *romain = malloc(20 * sizeof(char));
	romain[19] = '\0'; // 0 avant ?!
	int valeurs[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	char* symboles[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	if (1 <= a && a <= 3999)
	{
		for (int i=0; i < 13; i++)
		{
			while (a >= valeurs[i]) {
				strcat(romain, symboles[i]);
				a -= valeurs[i];
			}
		}
		return romain;
	}
	else
	{
		printf("%d n'est pas entre 1 et 3999", a);
		return NULL;
	}
}




int main()
{
    //Ex 20:
    bool tab[]= {true,true,true,true,false,true,true,false,true,false}; 
    printf("Le premier terme est %s et il y a %d terme(s) identique(s) avant le premier terme différent\n", tab[0] ? "true" : "false", spitze(tab,10));

    //Ex 21:
    if (nul(tab, 10))
    {
        printf ("La condition est vérifiée\n");
    }
    else
    {
        printf ("La condition n'est pas vérifiée\n");
    }

    //Ex 22:
    double a=-58.3;
    double b=3.6;
    printf("Le reste de %f par %f est %f", a, b, modfloat(a,b));

    //Ex 23:
    int t[]={3,-5,9,-12,46,-85,56,-89,-8,3};
    minmax(t,10);
    printf("Le minimum est %d et le max est %d\n", result.min, result.max);

    //Ex 24:
    int t[]= {3,56,9,-12,56,-85,56,-89,-8,56};
    printf("L'indice médian parmi les occurrences du maximum est: %d\n", medianemax(t,10));

    //Ex 25:
    double t[]={1,2,3};
    derive(t, 3);
    printf("Le polynôme dérivé est:\n");
    for (int i = 0; i < 3; i+=1) 
    {
        printf("%f ", t[i]);
    }

    //Ex 26:
    double t1[]={1,2,3};
    double t2[]={4,5,6,7};
    printf("Le produit des polynômes est:\n");
    double *p=multpol(t1,3,t2,4);
    for (int i = 0; i < 3+4-1; i++) 
    {
        printf("%f", p[i]);
    }
    free(p);

    //Ex 28:
    int nb=666;
    char *romain = auguste(nb);
    printf("%d en chiffre romain s'écrit: %s", nb, romain);
    free(romain);





    return 0;
}