## Ezequiel : A2, C3, F1, G1, J3, M3, N1, N3, Q1
## 1 : correction, 2 : terminaison, 3 : complexité

### A: terminaison
Il faut entrer un exposant à l'origine, de plus les deux arguments à passer
sont des flottants (donc pas des entiers, donc consigne non respectée).

### C : complexité
O(n) mais avec l'opérateur cons, beaucoup plus :D
O(n) => O(n^2)    (donc pas fifou)

### F : correction
List.tl => parcours la liste à chaque étape
@ => plus grande complexité inutile (O(n^2) au lieu de O(n))
retourner plutôt ([], [])

de plus, renvoie une erreur si la liste est vide (or, va continuer
à parcourir la liste jusqu'à plus d'élément)

```ocaml
let coupe l =
  let rec aux l (l1, l2) toggle =
    match l with
    | [] -> (List.rev l1, List.rev l2)
    | x :: xs -> if toggle then aux xs (x :: l1, l2) (not toggle)
                 else aux xs (l1, x :: l2) (not toggle)
  in aux l ([], []) true;;

(* sinon le code du prof est mieux *)
```

### G : correction
@ => plus grande complexité inutile
l => à remplacer par une accumulation directe

```ocaml
let colle l1 l2 = 
  let rec collage acc l1 l2 = match (l1, l2) with
    | [], [] -> List.rev acc
    | a :: s, b :: t -> collage (b :: a :: acc) s t
    | a :: s, [] -> collage (a :: acc) s []
    | [], b :: t -> collage (b :: acc) [] t
  in collage [] l1 l2;;

(* sinon le code du prof est mieux *)
```

### J : complexité
List.length => O(n)
combien => O(n)
total => O(n^2)
meilleur : O(n)

### M : complexité
Soit n la longueur de la liste l1 et m la longueur de la liste l2.
O(min(n, m)) (donc correct)

### N : correction
Déjà pourquoi failwith quand c'est identique ?
Elles sont donc bel et bien dans le même ordre (lexicographique).
Les `then true` et `then false` c'est pour m'achever ?

```ocaml
let rec lexico l1 l2 = match l1 with
    | [] -> l2 = [] (* et encore... *)
    | a::q -> match l2 with
        | [] -> false
        | b::r -> a < b || (a = b && lexico q r);;
```

### N : complexité
Bon apparement, la complexité est bonne.
Pour n la longueur de la liste l1 et m la longueur de la liste l2, on a :
O(min(n, m))     (donc correct)

### Q : correction
@ => plus grande complexité inutile
ap => crée des listes intermédiaires inutiles
récursion terminale => pas bien

```ocaml
(* le code du prof est mieux *)

(* Sinon avec des opérateurs cons *)
let rec aplatir lst =
	match lst with
	| [] -> []
	| x::reste -> x@(aplatir reste)
;;

(* Ou alors, en trichant un tout pitit peu : *)
let aplatir l =
  List.fold_left (fun acc sublist -> acc @ sublist) [] l;;
```
