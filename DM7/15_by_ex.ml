type couleur = Pique | Coeur | Carreau | Trefle;;
type valeur = A | R | D | V | Autre of string;;


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
  true_val: int; 
  val_suite: int; 
};;


let val_of_valeur card =
  match card with
  | Autre(a) -> if a = "10" then 10 else int_of_string a
  | V -> 10
  | D -> 10
  | R -> 10
  | A -> 1;;

let val_pour_suite card =
  match card with
  | Autre(a) -> if a = "10" then 10 else int_of_string a
  | V -> 11
  | D -> 12
  | R -> 13
  | A -> 1;;


let combinaisons nombre =
  match nombre with
  | 1 -> 0
  | 2 -> 2
  | 3 -> 6
  | 4 -> 12
  | _ -> 0;;


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
    Hashtbl.replace dupl card.valeur (match Hashtbl.find_opt dupl card.valeur with
    | None -> 1
    | Some n -> n + 1)
  ) main_simple;



  (* COMBINAISONS *)
  pts := !pts + (Hashtbl.fold (fun _ count acc -> acc + combinaisons count) dupl 0);


  (* 15 *)
  let rec ex_15 (valeur_actuelle: int) (* mon journal préféré *) (restant: carte_mais_simple list) =
    let count = ref 0 in
    
    List.iteri (fun i el -> 
      if valeur_actuelle + el.true_val = 15 then incr count
      else if valeur_actuelle + el.true_val < 15 then
        count := !count + ex_15 valeur_actuelle + el.true_val (List.filteri (fun j _ -> i <> j) restant)
    ) restant;
  
    !count

  pts :=  !pts + ex_15 0 Array.to_list main_simple


  (* SUITES *)

  let length_suite = ref 0 in
  let curr_length = ref 0 in
  let cartes_in = ref [] in
  Array.fast_sort (fun card1 card2 -> card1.val_suite - card2.val_suite) main_simple;
  
  for i = 0 to 4 do
    for y = i+1 to 4 do
      if not(y-!curr_length < 3) then
        (
          if main_simple .(y).val_suite - main_simple .(y-1).val_suite = 1 then (
            if !curr_length = 0 then cartes_in := [main_simple .(y-1)]
            
            cartes_in := (main_simple .(y))::(!cartes_in);
            incr curr_length;
          )
          else if !curr_length <> 0 then (
            if !curr_length > 3 then length_suite := max (!length_suite) (!curr_length)
            else (
              curr_length := 0; 
              cartes_in := [];
            )
        )
    done;
  done;

  curr_length := !length_suite
  List.iter (fun el -> length_suite := !length_suite + !curr_length * ((Hashtbl.find dupl el.valeur) - 1)) (!cartes_in);

  pts := !pts + !curr_length;


  (* ONE FOR HIS NOB *)
  if Array.exists (fun card ->
      (get_machin_associe_valeur card.valeur) = V &&
      (get_machin_associe_couleur card.couleur) = (get_machin_associe_couleur extra.couleur)
    ) main
  then pts := !pts + 1;


  
  (* COULEUR *)
  let fst = main_simple.(0).couleur in
  if Array.fold_left (fun acc el -> el.couleur = fst && acc) true main_simple then (
    if extra.couleur = fst then incr pts
    incr pts;
  )


  !pts
;;
