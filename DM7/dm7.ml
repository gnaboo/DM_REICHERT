
(* Exercice 60 *) (* COMPILE *)
let pgcd fst scn = 
  let a = ref (max fst scn) in
  let b = ref (min fst scn) in
  let r = ref (!a mod !b) in
  while !r <> 0 do
    a := !b;
    b := !r;
    r := !a mod !b;
  done;
  !b;;

let mcnuggets a b = 
  if pgcd a b = 1 then failwith "Il n'existe pas de nombre de mcnuggets";
  a * b -b -a;;



(* Exercice 61 *) (* COMPILE *)
let existesomme (tab: int array) : bool = 
  let ret = ref false in
  for i = 0 to (Array.length tab - 1) do
    if(not !ret ) then
    for y = 0 to (Array.length tab - 1) do
      if(not !ret && i <> y) then
      for x = 0 to (Array.length tab - 1) do
        if y <> x && tab.(i) = tab.(y) + tab.(x) then ret := true
      done;
    done;
  done;
  !ret;;


(* Exercice 62 *) (* COMPILE *)
let fincommune (str1: string) (str2: string) : int = 
  let counter = ref 0 in
  let size1 = (String.length str1) in
  let size2 = (String.length str2) in
  let min_len = min size1 size2 in
  for i = 0 to (min_len - 1) do
    if(i = !counter && str1.[size1-i-1] = str2.[size2-i-1]) then incr counter
  done;
  !counter;;


(* Exercice 63 *) (* COMPILE *)
type fraction = { nom: int; denom: int;};;
let simplifiable (tab: fraction array) : bool = (* O(n^2) si jamais on fait chaque fraction avec celle d'après... *)
	let is_same x1 x2 y1 y2 = x1*y2 = y1*x2 in (*\forall (x, x')\in\mathbb{Z}^2, (y, y') \in \mathbb{Z}^{*}\times\mathbb{Z}^{*}\\ \frac{x}{y} = \frac{x'}{y'} \Longleftrightarrow xy' = yx'*)
	let result = ref false in
	for i = 0 to (Array.length tab -1) do
		if not !result then
		begin		
		for y = (i+1) to (Array.length tab -1) do
			result := tab.(i).denom * tab.(y).denom <> 0 && is_same (tab.(i).nom) (tab.(y).nom) (tab.(i).denom) (tab.(y).denom)
		done;
		end
	done;
	!result;;

(* Exercice 64 *)
type 'a lc = { mutable tete : 'a option; mutable suivant : 'a lc option };;
let creer_lc() = { tete = None; suivant = None };;
let rec taille_lc l =
  match l.tete, l.suivant with
  | None, _ -> 0
  | _, None -> 1
  | _, Some reste -> 1 + taille_lc reste;;

let rec inserer_lc l i x =
  match i, l.tete, l.suivant with
  | 0, None, _ -> l.tete <- Some x
  | 0, Some a, None -> let reste = { tete = Some a; suivant = None } in l.tete <- Some x; l.suivant <- Some reste
  | 0, Some a, Some reste -> let lbis = { tete = Some a; suivant = Some reste } in l.tete <- Some x; l.suivant <- Some lbis
  | _, None, _ -> failwith "Liste chaînée trop courte"
  | 1, _, None -> let reste = { tete = Some x; suivant = None } in l.suivant <- Some reste
  | _, _, None -> failwith "Liste chaînée trop courte"
  | _, _, Some reste -> inserer_lc reste (i-1) x;;



let miroirlc (lcv: 'a lc) = 
  let taille = taille_lc lcv in
  match taille with 
  | a when a < 1 -> creer_lc ()
  | size -> 
    let new_lc = creer_lc () in
    let next = ref lcv in
    for i = 0 to (size - 1) do
      inserer_lc new_lc i (!next.tete);
      next := (match !next.suivant with | Some s -> s | _ -> failwith "Suicide toi");
    done;
    new_lc;;
      






(* Exercice 65 *) (* COMPILE *)
let sommeminmax (arr: int array) : int =
  Array.fast_sort (fun x y -> x - y) arr;
  let counter = ref 0 in
  for i = 0 to (Array.length arr - 1) do
  	if i mod 2 = 0 then counter := !counter + (max (arr.(i)) (arr.(i+1)));
  done;
  !counter;;



(* Exercice 66 *)
let build_frequency_table arr =
  let table = Hashtbl.create (Array.length arr) in
  Array.iter (fun x ->
    let count = Hashtbl.find_opt table x |> Option.value ~default:0 in
    Hashtbl.replace table x (count + 1)
  ) arr;
  table
;;

let max_frequency table =
  Hashtbl.fold (fun _ count acc -> max acc count) table 0
;;

let values_with_max_freq table max_freq =
  Hashtbl.fold (fun key count acc -> if count = max_freq then key :: acc else acc) table []
;;

let indices_of_value arr value =
  let indices = Array.fold_left (fun (idxs, i) x -> 
    if x = value then (i :: idxs, i + 1) else (idxs, i + 1)
  ) ([], 0) arr in
  List.rev (fst indices)
;;

let median_of_sorted_list lst =
  let len = List.length lst in
  if len = 0 then None
  else if len mod 2 = 1 then Some (List.nth lst (len / 2))
  else Some (List.nth lst ((len / 2) - 1))
;;

let medianefreq arr =
  let size = Array.length arr in
  if size < 3 then 0 else
  let table = build_frequency_table arr in
  let max_freq = max_frequency table in
  let values = values_with_max_freq table max_freq in

  let indexed_values = 
    List.map (fun v ->
      let indices = indices_of_value arr v in
      let sum_indices = List.fold_left ( + ) 0 indices in
      let median_index = median_of_sorted_list indices |> Option.get in
      (sum_indices, median_index, v)
    ) values
  in

  let _, min_median, _ = List.fold_left (fun (max_sum, min_med, best_value) (sum, median, value) ->
    if sum > max_sum then (sum, median, value)
    else if sum = max_sum && median < min_med then (sum, median, value)
    else (max_sum, min_med, best_value)
  ) (0, size, 0) indexed_values in

  min_median
;;






(* Exercice 67 *) (* COMPILE *)
let niederschaeffolsheim (str: string) : int =
  let compteur = ref 0 in
  let maxi = ref 0 in
  String.iter (fun el -> 
    if el = ' ' then (
      if !compteur <> 0 then (
        if !compteur > !maxi then maxi := !compteur;
        compteur := 0
      )
    ) else 
      incr compteur
  ) str;
  
  if !compteur > !maxi then maxi := !compteur;
  !maxi ;;


(* Exercice 68 *) (* COMPILE *)
let is_prime num = if num mod 2 = 0 then num = 2
else begin
  let rec aux counter = 
    if num = counter then true
    else (num mod counter <> 0) && aux (counter+2)
  in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
end;;

let stringify car = String.make 1 car;;

let kneckes (str: string) : string = 
  let compteur = ref 0 in
  let new_str = ref "" in
  let length = String.length str in
  String.iteri (fun i el -> 
      if el = ' ' && i+1 <> length then (
        incr compteur;
        if is_prime !compteur then new_str := !new_str ^ " hopla"
      );
      new_str := !new_str ^ (stringify el)
    ) str;
  !new_str;;


(* Exercice 69 (jolie nombre) *) (* Ne compile pas, j'ai passé 1h à chercher l'erreur et j'ai pas trouvé...*)
(* Horriblement long (5h dessus pour même pas finir) et d'une difficulté énorme *)
(* J'espère que ces efforts seront récompensés *)
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







