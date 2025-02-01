Ezequiel : A2, C3, F1, G1, J3, M3, N1, N3, Q1 \
Gabriel : D2, H1, H2, K3, N2, O1, P1, P2, Q3 \
Léo-Paul : A1, B1, C2, E3, I1, M2, O2, O3, Q2 \
Olympe : E1, E2, F2, G2, J2, L2, L3, M1 \
Cyann : A3, B3, C1, D1, H3, J1, L1, P3 \
Rhita : B2, D3, F3, G3, I2, I3, K1, K2

# Résumé
## Fonction A
Mauvais typage, trop d'arguments \
Asymptotiqument, complexité doublée \
### Terminaison à faire Ezequiel :p
Theta(log(n))

## Fonction B
len(liste) < 5 pas pris en compte \
Boucle while qui termine ici pour !r > 5, ce qui arrive à un moment donné selon la liste qu'on soumet au programme. \
Theta(n)

## Fonction C
Elémentaire mon cher Watson.
La disjonction de cas est bien faite. Je cite : "si on considère la fonction sans la mention rec : on initialise deux listes, puis on entre dans une boucle conditionnelle soit l'invariant "si il y a des éléments dans les listes b et c, les éléments d'indice pair de la liste originelle sont tous dans la liste b et les éléments d'indice impairs sont dans la liste c et dans le même ordre "quand i = 0, les listes b et c sont vides donc l'invariant est satisfait - si i est pair, on ajoute l'élément d'indice i de la liste originelle à la fin de la liste b, donc l'invariant est satisfait - si i est impair, on ajoute l'élément d'indice i de la liste originelle à la fin de la liste c, donc l'invariant est satisfait quelque soit la valeur de i, l'invariant est satisfait, donc la fonction (sans la mention rec) renvoie bien un couple avec dans la première liste les éléments d'indice pair de la liste originelle et dans la deuxième les éléments d'indices impairs dans le même ordre. \
Elle se termine toute fois bien, prenons comme variant de boucle v = taille(l)-1-i. A chaque tours de boucle i augmente de 1 donc v reduit de 1 à chaque tours. La boucle s'arrete lorsque i = taille(l) -1 ce qui correspont alors v = 0. V est donc bien strictement décroissante jusque 0. La boucle se termine donc bien et alors le programme aussi. CQFD
O(n^2)    (donc pas fifou)

## Fonction D
la fonction comprend une fonction récursive, avec en argument k, que l'on peut assimiler à un vérificateur de parité, x l'indice de l'élément observé et une liste soit l'invariant "si il y a des éléments dans la liste en arguments, si son indice est pair, il est envoyé dans la premiere liste du couple sinon, il est envoyé dans la deuxième liste du couple dans le même ordre" on considère k = 0 : deux possibilités : - si la liste en argument est vide on renvoie une liste vide et alors l'invariant est respecté - si la liste n'est pas vide, on vérifie la parité de x, si x est pair, on ajoute le premier élément de la liste au début de la liste renvoyée puis on appelle la fonction avec le reste de la liste en paramètre donc l'invariant est respecté si x est impair, on ajoute pas le premier élément de la liste au début de la liste renvoyée puis on appelle la fonction avec le reste de la liste en paramètre donc l'invariant est respecté et symétriquement pour k = 1, donc à chaque appel de la fonction, l'invariant est respecté, donc aux 0 0 liste renvoie les éléments d'indice pair de la liste et aux 1 0 liste renvoie les éléments d'indice impair de la liste, donc le couple renvoyé est correct \
### Il a pas fait la terminaison. \
O(n)

## Fonction E
Correction: la fonction coupe vérifie les 3 cas possibles: 
	- lorsque la liste est vide alors la fonction renvoie 2 listes vides
	- lorsque la liste contient qu'un seul élément alors seulement la première liste envoyée a cet élément
	- lorsque la liste est remplie, la fonction s'occupe de trier en alternant le remplissage des 2 listes renvoyés
Dans les 3 cas, la fonction renvoie 2 listes possédant les éléments alternés de la liste entrée en argument
Terminaison: la liste entrée en argument est soit vide soit remplie avec un élément soit remplie avec plusieurs éléments. La fonction coupe va avancer au fur et à mesure dans les éléments et va forcément finir par atteindre le cas d'une liste vide et donc la fonction se termine en renvoyant 2 listes avec la liste de base coupée.
### C'est Léo-Paul qui l'a pas fait.

## Fonction F
### Bah Ezequiel, retourne bosser c'est incomplet
Terminaison: La fonction se finit par une erreur sauf si la liste en argument est un singleton. La liste est parcourue jusqu'à ce qu'il ne reste qu'un élément vide qui provoque une erreur de List.tl ou List.hd ou simplement si la liste d'origine est vide alors il y a le message d'erreur "Oups" \
le @ n'est pas recommandé (complexité linéaire, parcourt la liste)
ici, complexité O(n²)

## Fonction G
### Ezequiel, retourne bosser c'est incomplet
Terminaison: La fonction progresse à chaque fois d'un élément dans l1 et l2 jusqu'à n'obtenir que 2 listes vides et retourner le résultat l
### Rhita ne sait pas si c'est cubique ou pas exactement (en tout cas, y'a un "@", donc pas linéaire)

## Fonction H
Des bouts de code complètements cons:
 -> compare un booléan...
 -> sommesi + 0 = sommesi il me semble (peut être que Mr Havret nous a caché des choses mais je crois pas) \
### Gabriel, retourne bosser c'est incomplet
O(n) (voir démo de Cyann : "on considère la complexité du prédicat comme O(1) on considère la correction et la terminaison du programme on prendra en compte les additions et les comparaisons comme opérations élémentaires à chaque appel 2 possibilités : - la liste est vide -> O(1) - la liste n'est pas vide -> si le prédicat est vrai : O(1) et appel suivant, avec une comparaison inutile ( pred(a) renvoie déjà un booléen ) si le prédicat est faux : O(1) et appel suivant, avec une somme inutile ( 0+ sommesi = sommesi )  conclusion : complexité de O(3n) alors qu'en retirant les comparaisons et sommes, on pourrait avoir une complexité de O(2n)")

## Fonction I

