(* 

Repartition du travail:
Gabriel : P1, H2, N2, H1, K3, P2, O1, D2, Q3

1 : correction, 2 : terminaison, 3 : complexité 


*)


(* Fonction D *)

let coupe liste=
let rec aux k x liste =
match liste with
|[]->[]
|a::q-> if x mod 2 =k then a::(aux k (x+1) q) else aux k (x+1) q in
(aux 0 0 liste, aux 1 0 liste);;

(* Exercice 36 *)

(* Fonction H *)

let rec sommesi list pred =
  match list with
  |[] -> 0
  |a::reste -> if pred a = true then a+sommesi reste pred else 0+sommesi reste pred;;

(* Des bouts de code complètements cons:
 -> compare un booléan...
 -> sommesi + 0 = sommesi il me semble (peut être que Mr Havret nous a caché des choses mais je crois pas)
 *)

(* -- *)

(* Exercice 37 *)

(* Fonction K *)

let majopred liste predicat = 
let rec aux liste predicat = match liste with
|[]-> 0
|a::q -> if predicat a then 1 + aux q predicat else aux q predicat
in let taille = List.length liste 
in if aux liste predicat > taille / 2 then true else false;;

(* 
 -> Une fonction auxiliaire avec la même signature que la fonction de base... pourquoi pas ?
 -> déclaration de variable taille inutile (une seule utilisation dans la fonction...)
 -> if(bool) à la fin... pour renvoyer (bool)
 *)

(* Fonction N *)

let rec lexico l1 l2 = match l1 with 
	|[] -> if l2=[] then failwith ("liste identiques") else true
	|a::q -> match l2 with
	|[] -> false
	|b::r -> if a<b then true else if a>b then false else lexico q r;;

(* L'absence d'indentation laisse croire qu'il s'agit du même match entre l1 et l2
 -> Possibilité d'écrire la dernière ligne comme opération logique avec des && et des || grace à la paresse d'Ocaml
 *)

(* Exercice 19 *)

(* Fonction O *)

let rec aplatir l1 l2 = match l1 with
  | [] -> l2
  | a::q -> a::(aplatir q l2) ;; 

(* Pas optimisé si Array.length l1 >> Array.length l2*)

(* Fonction P *)

let aplatir l1 =
    let nlist = ref [] in
    let tab = Array.of_list l1 in
    
    for i = 0 to ((Array.length tab)-1) do 
    
    nlist:= !nlist @ tab.(i)
    done ; nlist ;;

(* Implique un tableau et non une liste (qui ne sont pas les mêmes objects en OCaml) donc non-respect de la signature ! *)
(* Le programme est au delà de ça esthétique *)

(* Fonction Q *)

let aplatir l1 =
  let rec ap l1 l2= match l1 with
    |a::q-> ap q (l2@[a])
    |[]->l2
  in
  let rec app l1 lresult= match l1 with
    |a::q -> app q (lresult@ap a [] )
    |[] -> lresult
  in
  app l1 [];;

(* Implique un tableau et non une liste (qui ne sont pas les mêmes objects en OCaml) donc non-respect de la signature ! *)
(* Le programme est au delà de ça esthétique *)