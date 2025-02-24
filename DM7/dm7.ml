
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
    for y = i+1 to (Array.length tab - 1) do
      if(not !ret ) then
      for x = y+1 to (Array.length tab - 1) do
        if tab.(i) = tab.(y) + tab.(x) then ret := true
      done;
    done;
  done;
  !ret;;


(* Exercice 62 *) (* COMPILE *)
let fincommune (str1: string) (str2: string) : int = 
  let counter = ref 0 in
  let min_len = min (String.length str1) (String.length str2) in
  for i = 0 to (min_len - 1) do
    if(i = !counter && str1.[i] = str2.[i]) then incr counter
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



(* Exercice 66 *)  (* PAS TERMINé !*)

let medianefreq (tab: 'a' array) : int =
  let size = Array.length tab in
  if size = 0 then failwith "Vive la Belgique"

  let tbl = Hashtbl.create in
  Array.iteri (fun i el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
  | Some((a, ind)) -> (a + 1, ind + i)
  | None -> (1, i)
  )) tab;

  let freq_max_el = Hashtbl.fold (fun acc _ value -> match acc, value with
  | Some(acc_val, acc_ind), Some(val_val, val_ind) -> if val_val >= acc_val then (if val_ind > acc_ind then value else acc) else acc
  ) (Hashtbl.find tbl (tab.(0))) tbl 

  in

  let abis = Array.make (Array.length tab) 0 in

  Array.iteri (fun i el -> if el = freq_max_el then abis.(i) = i);

  abis = Array.map (fun el -> el <> 0) abis;






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
  String.iter (fun el -> 
      if el = ' ' then (
        incr compteur;
        if is_prime !compteur then new_str := !new_str ^ " hopla"
      );
      new_str := !new_str ^ (stringify el)
    ) str;
  !new_str;;


(* Exercice 69 (jolie nombre) *)
let kakaboudin (arr: int array) : int =
  Array.fast_sort (fun x y -> x - y) arr;
  let counter = ref 0 in
  for i = 0 to (Array.length arr - 1) do
  	if i mod 2 = 0 && then counter := !counter + (max (arr.(i)) (arr.(i+1)));
  done;
  !counter;;


let crib (main: carte array) : int = 
  let main = [|main.(0) ; main.(1); main.(2); main.(3); extra|] in
  let pts = ref 0 in

  let ctr = ref 0 in
  let dupl = Hashtbl.create in
  Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
  | None -> 1
  | Some a -> a + 1
  )) tab;

  Hashtbl.iter (fun key val -> if val < 2 then Hashtbl.remove tbl key)

  (* 15 *)

  let dupl_in_15 = ref 0 in
  let added = ref [] (* j'en ai plus rien à foutre, O(4) = O(1) = O(Ackermann(42, 42)) *)

  let new_arr = Array.init (fun el -> ctr := ctr + el; added := (el::(!added))
    if !ctr = 15 then (List.iter (!added) (fun el -> if Array.mem dupl el then incr dupl_in_15); !added = []; 0) 
    else !ctr mod 15) main in

  let tbl = Hashtbl.create in

  Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
  | None -> 1
  | Some a -> a + 1
  )) tab;

  let sum = Hashtbl.fold (fun acc _ val -> acc + val) 0 tbl in
  pts := (sum + !dupl_in_15) * 15;

  (* SUITE *)

  let length = ref 0 in
  Array.fast_sort (fun x y -> x - y) main;
  
  for i = 0 to 4 do
    for y = i+1 to 4 do
      if not(y-!length < 3) then
        (
          if 



        )
  
  










