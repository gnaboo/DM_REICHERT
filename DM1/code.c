/* 

        NOTE: 15/20

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// OUTILS GENERAUX
void test_bool(bool var)
{
    if (var)
        printf("true\n");
    else
        printf("false\n");
}

void display_tableau(int *tableau, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        printf("arg: %d:%c\n", i, tableau[i]);
    }
    printf("\n");
}

void init_list(char *liste, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        liste[i] = 0;
    }
}

// UTILITAIRE EXO 14
int char_to_int(char car)
{
    // on prC)sume que le caractere est forcement un entier
    return (car - 48);
}

// UTILITAIRE EXO 16
bool isinlist(char *tableau, int taille, int element)
{
    for (int i = 0; i < taille; i++)
    {
        if (tableau[i] == element)
            return true;
    }
    return false;
}

// UTILITAIRE EXO 14 et 17
int reverse_int(int number)
{
    int placeholder = 0;
    while (number > 0)
    {
        placeholder = placeholder * 10 + number % 10;
        number = number / 10;
    }
    return placeholder;
}

// UTILITAIRE EXO 18

bool is_number(char car)
{
    return (car >= 48) && (car <= 57);
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

bool palindrom_str(char *string)
{
    int taille = (int)strlen(string) - 1; // cast en int depuis size_t (long unsigned int) - 1;
    for (int i = 0; i < taille; i++)
    {
        if (string[i] != string[taille - i])
        {
            return false;
        }
    }
    return true;
}

// UTILITAIRE EXO 19

int extraire_position(char *string) // oh tiens, un copié collé
{
    int size = (int)strlen(string); // cast en int depuis size_t (long unsigned int);
    bool found = false;
    int counter = 0;

    for (int i = 0; i < size; i++)
    {
        if (is_number(string[i]))
        {
            found = true;
        }
        else if (found)
        {
            break;
        }
        counter++;
    }
    if (counter == 0)
        counter = size;
    return counter;
}

void cut_string(char *string, int position)
{
    int taille = (int)strlen(string); // cast en int depuis size_t (long unsigned int);
    for (int i = 0; i < position && i < taille; i++)
    {
        string[i] = 'X'; // a chosen null car
    }
}


// ---------------------------------------------------------------------------------------------------------
// -------------------------------------------------FONCTIONS-----------------------------------------------
// ---------------------------------------------------------------------------------------------------------



// EXO 10
float fraction(int num1, int num2)
{
    if (num2 == 0)
        exit(133);
    return (float)num1 / num2;
}

// EXO 11
bool bissextile(int year)
{
    if (year < 2000)
        return false;

    return ((!(year % 4) && (year % 100)) || (!(year % 100) && !(year % 400)));
}

// EXO 12
double evalue(double tableau[], int taille, double x)
{
    double placeholder = tableau[taille - 1];

    for (int i = 1; i < taille; i++)
    {
        placeholder = placeholder * x + tableau[taille - i - 1];
    }

    return placeholder;
}

// EXO 13
int ecartmin(int *tableau, int taille)
{
    int min = abs(abs(tableau[0]) - abs(tableau[1]));
    for (int i = 0; i < (taille - 1); i++)
    {
        if (abs(abs(tableau[i]) - abs(tableau[i + 1])) < min)
        {
            min = abs(abs(tableau[i]) - abs(tableau[i + 1]));
        }
    }
    return min;
}

// EXO 14
int extraire(char *string)
{
    int size = (int)strlen(string); // cast en int depuis size_t (long unsigned int);
    int position = 0;
    int placeholder = 0; // peut être unsigned
    short sign = 1;
    unsigned long long int power = 1; //[0; 18446744073709551615]
    char last_int = 0;

    for (int i = 0; i < size; i++)
    {
        if (is_number(string[i]))
        {
            placeholder += char_to_int(string[i]) * power;
            power *= 10;
            position += 1;
            last_int = string[i];
        }

        else if (string[i] == 45 && (i + 1 < size))
        {
            if (is_number(string[i + 1]))
            {
                sign = -1;
            }
            continue;
        }

        else if (position > 0)
        {
            break;
        }
    }

    if (last_int == '0')
    {
        placeholder = placeholder + (int)power;
        return (reverse_int(placeholder) - 1) * sign;
    }

    return reverse_int(placeholder) * sign;
}

// EXO 15
float sommemajo(float *liste, int taille)
{
    float sum_pos = 0;
    float sum_neg = 0;
    float balance = 0;
    for (int i = 0; i < taille; i++)
    {
        if (liste[i] > 0)
        {
            sum_pos += liste[i];
            balance += 1;
        }

        if (liste[i] < 0)
        {
            sum_neg += liste[i];
            balance -= 1;
        }
    }
    if (balance > 0)
    {
        return sum_pos;
    }
    if (balance < 0)
    {
        return sum_neg;
    }
    return 0;
}

// EXO 16
int nbdiff(char *string)
{
    int taille = (int)strlen(string); // cast en int depuis size_t (long unsigned int);
    char trouves[256];                // sans prendre on compte les nouveaux caracteres ascii
    init_list(trouves, 256);
    int position = 0;

    for (int i = 0; i < taille; i++)
    {
        if (!isinlist(trouves, 256, (int)string[i]))
        {
            trouves[position] = (int)string[i];
            position += 1;
        }
        else
        {
        }
    }
    return position;
}

// EXO 17
bool palindromint(int number)
{
    return number == reverse_int(number);
}



// EXO 18
bool palindrom2(char *string)
{
    int taille = (int)strlen(string); // cast en int depuis size_t (long unsigned int);
    char *new_string = malloc(sizeof(char) * taille);
    init_list(new_string, taille);
    int counter = 0;

    for (int i = 0; i < taille; i++)
    {
        if (is_letter(string[i]))
        {
            if (is_uppercase(string[i]))
            {
                new_string[counter] = string[i] + 32;
            }
            else
            {
                new_string[counter] = string[i];
            }
            counter += 1;
        }
    }
    new_string[counter] = '\0';
    bool value = palindrom_str(new_string);

    free(new_string);

    return value;
}

// EXO 19
int sommeentier(char *string)
{
    int taille = (int)strlen(string); // cast en int depuis size_t (long unsigned int);
    int somme = 0;
    int position = 0;
    int number;

    while (position < taille)
    {
        number = extraire(string);
        if (number != 0)
        {
            somme += number;
            position = extraire_position(string);
            cut_string(string, position);
        }
        else
            break;
    }
    return somme;
}

int main()
{
    // EXO 10 - fraction
    printf("---- EXO 10 - fraction ----\n");
    printf("%f\n", fraction(10, 5)); // 2.
    printf("%f\n", fraction(10, 3)); // 3.333333
    // printf("%f\n", fraction(10, 0)); // exit 133

    // EXO 11 - bissextile
    printf("---- EXO 11 - bissextile ----\n");
    test_bool(bissextile(2004)); // true
    test_bool(bissextile(2005)); // false
    test_bool(bissextile(1280)); // false

    // EXO 12 - evalue
    printf("---- EXO 12 - evalue ----\n");
    double liste[3] = {2., 3., -5.};
    printf("%f\n", evalue(liste, 3, 0.)); // 2.
    printf("%f\n", evalue(liste, 3, 1.)); // 2. + 3.*1. + (-5.) * 1. = 0.
    printf("%f\n", evalue(liste, 3, -2)); // 2. + 3.*(-2.) + (-5.) * (-2.)^2 =  2. - 6. -20. = -24.

    // EXO 13 - ecartmin
    printf("---- EXO 13 - ecartmin ----\n");
    int liste_2[7] = {2, 4, 6, -2, 1, 0, 0};
    printf("%d\n", ecartmin(liste_2, 7)); // 0
    printf("%d\n", ecartmin(liste_2, 5)); // 1
    printf("%d\n", ecartmin(liste_2, 3)); // 2

    // EXO 14 - extraire
    printf("---- EXO 14 - extraire ----\n");
    char string[120] = "la-si-c-est-vraiment-nul-18203deschiffres et des espaces et d'autres chiffres9394 pour rigoler";
    printf("%d\n", extraire(string)); // -18203
    char string_2[120] = "nan y'a rien ici, c'est juste pour troll le programme";
    printf("%d\n", extraire(string_2)); // 0
    char string_3[20] = "lesbordsc'estcool42";
    printf("%d\n", extraire(string_3)); // 42

    // EXO 15 - sommemajo
    printf("---- EXO 15 - sommemajo ----\n");
    float liste_3[10] = {1.4, -2.5, 3.5, 1.0, 56.2, 593.3, -382.2, 0.0, -1.0, -0.0};
    printf("%f\n", sommemajo(liste_3, 10)); // 654.

    // EXO 16 - nbdiff
    printf("---- EXO 16 - nbdiff ----\n");
    char string_4[80] = "zefkljdsklfjlkdsjfkljdlk";
    char alphabet[80] = "abcdefghijklmnopqrstuvwxyz";
    char char_bizarres[80] = "abcdEFGefg \n\r?°&~";
    printf("%d\n", nbdiff(string_4));      // 8
    printf("%d\n", nbdiff(alphabet));      // 26
    printf("%d\n", nbdiff(char_bizarres)); // 18
    printf("%d\n", nbdiff(""));            // 0

    // EXO 17 - palindromint
    printf("---- EXO 17 - palindromint ----\n");
    test_bool(palindromint(120));   // false
    test_bool(palindromint(18081)); // true
    test_bool(palindromint(0x58));  // true

    // EXO 18 - palindrom2
    printf("---- EXO 18 - palindrom2 ----\n");
    test_bool(palindrom2("KaY ak8é99éàÿ"));                               // true
    test_bool(palindrom2("KaY ak8 && | ÿ"));                              // true
    test_bool(palindrom2("KaY aZoP -- çék8 && | ÿ"));                     // false
    test_bool(palindrom2("Tu l'as trop ecrase, Cesar, ce Port-Salut !")); // true. Eh oui, c'est une phrase palindrome !

    // EXO 19 - sommeentier // un bébé renié de sommemajo et extraire
    printf("---- EXO 19 - sommeentier ----\n");
    // pour rappel: char string[120] = "la-si-c-est-vraiment-nul-18203deschiffres et des espaces et d'autres chiffres9394 pour rigoler";
    char string_5[120] = "12473_-434_-2083 284";
    printf("%d\n", sommeentier(string));   // -8809
    printf("%d\n", sommeentier(string_5)); // 10240

    // TOUTES LES VALEURS ONT ETES VERIFEES AVEC gcc (Ubuntu 13.2.0-23ubuntu4) 13.2.0

    return 0;
}
