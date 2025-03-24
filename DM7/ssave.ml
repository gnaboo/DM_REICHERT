(* Types de base *)
type couleur = Pique | Coeur | Carreau | Trefle;;
type valeur = A | R | D | V | Autre of string;;

(* Association d'une chaîne à une valeur *)
let get_machin_associe_valeur str =
  match str with
  | "A" -> A
  | "R" -> R
  | "D" -> D
  | "V" -> V
  | s   -> Autre s;;

let get_machin_associe_couleur str =
  match str with
  | "Pique"   -> Pique  
  | "Coeur"   -> Coeur
  | "Carreau" -> Carreau
  | "Trefle"  -> Trefle
  | _         -> failwith "Je ne suis pas raciste mais...";;

type carte = { valeur : string; couleur : string };;

type carte_mais_simple = {
  valeur: valeur;
  couleur: couleur;
  true_val: int;  (* pour le 15 *)
  val_suite: int; (* pour l'ordre dans les suites *)
};;

(* Conversion de la valeur pour le 15 *)
let val_of_valeur card =
  match card with
  | Autre(a) -> if a = "10" then 10 else int_of_string a
  | V -> 10
  | D -> 10
  | R -> 10
  | A -> 1;;

(* Conversion pour les suites (les rangs suivent ici A=1, V=11, D=12, R=13) *)
let val_pour_suite card =
  match card with
  | Autre(a) -> if a = "10" then 10 else int_of_string a
  | V -> 11
  | D -> 12
  | R -> 13
  | A -> 1;;

(* Calcul du nombre de points pour un nombre de doublons (paires, brelans, …) *)
let combinaisons nombre =
  match nombre with
  | 1 -> 0
  | 2 -> 2
  | 3 -> 6
  | 4 -> 12
  | _ -> 0;;

(* La fonction crib : on reçoit une main (tableau de 4 cartes) et une carte annexe *)
let crib (main: carte array) (extra: carte) : int =

  let all_cards = [|main.(0) ; main.(1); main.(2); main.(3); extra|] in

  let main_simple =
    Array.map (fun el ->
      { 
        valeur    = get_machin_associe_valeur el.valeur;
        couleur   = get_machin_associe_couleur el.couleur;
        true_val  = val_of_valeur (get_machin_associe_valeur el.valeur);
        val_suite = val_pour_suite (get_machin_associe_valeur el.valeur)
      }
    ) all_cards in 
  
  let pts = ref 0 in

  let dupl = Hashtbl.create in

  Array.iter (fun card ->
    Hashtbl.replace dupl (card.valeur) (match Hashtbl.find_opt dupl key with
    | None -> 1
    | Some n -> n + 1)
  ) main_simple;



  (* COMBINAISONS *)
  pts := !pts + (Hashtbl.fold (fun _ count acc -> acc + combinaisons count) dupl 0);


  (* 15 *)
  let dupl_in_15 = ref 0 in

  let added = Hashtbl.create in
  let added = ref [] (* j'en ai plus rien à foutre, O(4) = O(1) = O(Ackermann(42, 42)) *)

  let new_arr = Array.init (fun el -> 
    ctr := ctr + el; 
    Hashtbl.replace added el (match Hashtbl.find_opt added el with
    | None -> 1
    | Some a -> a + 1 
    );

    if !ctr = 15 then (
      List.iter (!added) (fun el -> if Hashtbl.find dupl el > 1 then incr dupl_in_15); 
      !added = []; 
      0
    ) 
    else !ctr mod 15
    ) main in

  let tbl = Hashtbl.create in

  Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
  | None -> 1
  | Some a -> a + 1
  )) tab;

  let sum = Hashtbl.fold (fun acc _ val -> acc + val) 0 tbl in
  pts := (sum + !dupl_in_15) * 2;



  (* SUITES *)

  let length_suite = ref 0 in
  let curr_length = ref 0 in
  let cartes_in = ref [] in
  Array.fast_sort (fun card1 card2 -> card1.val_suite - card2.val_suite) main;
  
  for i = 0 to 4 do
    for y = i+1 to 4 do
      if not(y-!curr_length < 3) then
        (
          if main.(y) - main.(y-1).val_suite = 1 then (
            if curr_length = 0 then cartes_in := [main.(y-1)]
            cartes_in := (main.(y))::(!cartes_in)
            incr curr_length;
          )
          else if !curr_length <> 0 then (
            if !curr_length > 3 then length_suite := max (!length_suite) curr_length
            else (curr_length := 0; cartes_in := [];)
        )
    done;
  done;

  curr_length := !length_suite
  List.iter (!cartes_in) (fun el -> length_suite := !length_suite + !curr_length * ((Hashtbl.find dupl el) - 1));

  pts := !pts + !curr_length;


  (* ONE FOR HIS NOB *)
  if Array.exists (fun card ->
      (get_machin_associe_valeur card.valeur) = V &&
      (get_machin_associe_couleur card.couleur) = (get_machin_associe_couleur extra.couleur)
    ) main
  then pts := !pts + 1;

  !pts
;;
