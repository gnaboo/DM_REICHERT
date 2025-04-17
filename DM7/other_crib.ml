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
  | _         -> failwith "Erreur couleur";;

type carte = { valeur : string; couleur : string };;

type carte_mais_simple = {
  valeur: valeur;
  couleur: couleur;
  true_val: int;
  val_suite: int;
};;

let val_of_valeur card =
  match card with
  | Autre s -> int_of_string s
  | V | D | R -> 10
  | A -> 1;;


let val_pour_suite card =
  match card with
  | Autre("10") -> 10
  | Autre a -> int_of_string a
  | V -> 11
  | D -> 12
  | R -> 13
  | A -> 1;;

let combinaisons nombre =
  match nombre with
  | 2 -> 2
  | 3 -> 6
  | 4 -> 12
  | _ -> 0;;

let filteri f liste =
  let rec aux i liste = match liste with
    | [] -> []
    | a::other -> if f i a then a::aux (i + 1) other else aux (i + 1) other
  in
  aux 0 liste;;
  

let rec ex_15 valeur_actuelle restant =
  let count = ref 0 in
  List.iteri (fun i el ->
    if (valeur_actuelle + el.true_val) = 15 then incr count
    else if (valeur_actuelle + el.true_val) < 15 then
      count := !count + ((List.length (List.filter (fun x -> x.true_val = el.true_val) restant)) * ex_15 (valeur_actuelle + el.true_val) (filteri (fun j _ -> i <> j) restant))
  ) restant;
  !count;;
  

let crib (main: carte array) (extra: carte) : int =
  let all_cards = Array.append main [|extra|] in
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


  let dupl = Hashtbl.create 10 in
  Array.iter (fun card ->
    Hashtbl.replace dupl card.valeur (match Hashtbl.find_opt dupl card.valeur with
      | None -> 1
      | Some n -> n + 1)
  ) main_simple;
  pts := !pts + Hashtbl.fold (fun _ count acc -> acc + combinaisons count) dupl 0;

  (* 15 bordel de merde *)
  pts := !pts + (ex_15 0 (Array.to_list main_simple)) * 2;

  (* Suites *)
  let sorted = Array.copy main_simple in
  Array.sort (fun c1 c2 -> compare c1.val_suite c2.val_suite) sorted;
  let max_suite = ref 0 in
  let curr_length = ref 1 in
  let cartes_in = ref [] in
  let i = ref 1 in
  while !i < Array.length sorted do
    if sorted.(!i).val_suite = sorted.(!i - 1).val_suite + 1 then (
      if !curr_length = 1 then cartes_in := [sorted.(!i - 1)];
      cartes_in := sorted.(!i) :: !cartes_in;
      incr curr_length;
    )
    else if sorted.(!i).val_suite <> sorted.(!i - 1).val_suite then (
      curr_length := 1;
      cartes_in := [];
    )

    max_suite := max !max_suite !curr_length;
    incr i
  done;
  if !max_suite >= 3 then (
    let results = ref 0 in
    List.iter (fun el -> 
      results := !results + !max_suite * (Hashtbl.find dupl el.valeur - 1)
    ) !cartes_in;
    pts := !pts + !results;
  );

  (* "One for his nob" *)
  let couleur_extra = get_machin_associe_couleur extra.couleur in
  if Array.exists (fun card -> card.valeur = V && card.couleur = couleur_extra) main then
  incr pts;

  (* Couleurs *)
  let first_color = main_simple.(0).couleur in
  if Array.for_all (fun card -> card.couleur = first_color) main then (
    pts := !pts + 4;
    if (get_machin_associe_couleur extra.couleur) = first_color then incr pts;
  );

  !pts;;
