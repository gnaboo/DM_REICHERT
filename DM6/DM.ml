


(* Exercice 50 *)
let tables (n: int): (int * int) = 
	if n <= 6 then failwith "sale fils d'option si" else match n mod 4 with
	| a when a = 0 -> (n/4, 0)
	| a when a = 1 -> (n/4 + 1, -1)
	| a when a = 2 -> (n/4 + 2, -2)
	| a when a = 3 -> (n/4, 1);;

-

(* Exercice 51 *)
let q1 (a: 'a array): 'a array =
	let size = Array.length a in
		if size mod 4 <> 1 then failwith "Array size must be 4n + 1"
		else Array.init ((size - 1) / 4) (fun i -> a.(i))
;;



(* Exercice 52 *)
let minecart (tab: int array): int = 
	let abs a = if a < 0 then -a else a in let min = ref (abs (tab.(0))) in 
	Array.iteri (fun i el -> if abs(el - i) < !min then min := abs(el - i)) tab;
	!min;;



(* Exercice 53 *)
let premiercommepremier (arr: 'a array): int = 
	let num = ref (-1) in
	Array.iteri (fun i el -> if el = arr.(0) && !num = -1 && i <> 0 then num := i) arr;
	!num;;



(* Exercice 54 *)
let premiercommeavant tab = 
	let cpl = ref (-1, -1) in
	let found = ref false in
	for i = 1 to Array.length tab -1 do
		if not(!found) then
		for j = 0 to i-1 do
		if (tab.(i)=tab.(j)) && (!cpl = (-1, -1)) then (cpl := (i,j); 
			found:=true)
	done;
	done; !cpl;;




(* Exercice 55 | L'enfer *)
	let equilibre tab = let tbl = Hashtbl.create (Array.length tab) in
	Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
		| None -> 1
		| Some(a) -> a + 1)) tab;
	let first = Hashtbl.find tbl tab.(0) in
	let arr = Array.make (Hashtbl.length tbl) 0 in
	let ind = ref 0 in
	Hashtbl.iter (fun _ valeur -> arr.(!ind) <- (valeur - first); incr ind) tbl;
	Array.fold_left (fun acc valeur -> acc && (valeur = 0)) true arr;;



(* Exercice 56 *)
let premierabsent (table: int array): int =
	let size = Array.length table in
	if size = 0 then 0 else let min = ref table.(0) in
		for i = 1 to size - 1 do
			if table.(i) < !min then min := table.(i)
		done;
	if !min > 0 then 0 else !min - 1
;;



(* Exercice 57 *)
let rpz (s: string): int =
	let size = String.length s in
	let counts = Array.make 5 0 in
		for i = 0 to size - 1 do match String.get s i with
			| 'm' | 'M' -> counts.(0) <- counts.(0) + 1
			| 'o' | 'O' -> counts.(1) <- counts.(1) + 1
			| 's' | 'S' -> counts.(2) <- counts.(2) + 1
			| 'e' | 'E' -> counts.(3) <- counts.(3) + 1
			| 'l' | 'L' -> counts.(4) <- counts.(4) + 1
			| _ -> ()
		done;

		counts.(3) <- counts.(3) / 2;
		counts.(4) <- counts.(4) / 2;

	Array.fold_left (fun acc x -> if x < acc then x else acc) counts.(0) counts
;;



(* Exercice 58 *)
let decomp n = let get_next_prime n = let next = ref (n+1) in let is_prime num = if num mod 2 = 0 then num = 2
		else begin
		let rec aux counter = 
		if num = counter then true
		else (num mod counter <> 0) && aux (counter+2)
		in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
		end in
		while not (is_prime !next) do
			incr next;
		done;
		!next in 
	let rec aux liste copy prime = 
		if copy = 1 then liste
		else
		begin
			if copy mod prime = 0 then match liste with
			| (p, n)::q when p = prime -> aux ((p, n+1)::q) (copy/prime) prime (* MARCHE !*)
			| _ -> aux ((prime, 1)::liste) (copy / prime) prime
			else aux liste copy (get_next_prime prime)
		end
		in aux [] n 2;;




(* Exercice 59 *)
(* Incompréhensible, j'ai implémenté un compteur de point de la scopa à la place *)

type couleur = Epee | Massue | Vase | Or;;
type valeur = Roi | Dame | Cavalier | Sept | Nombre of int;;
type carte = {valeur : valeur ; couleur : couleur ; upside: bool};;

let valeur_pile (pile: carte array): int * int * int = 
	let sette = ref 0 in
	let valeur_totale = ref 0 in
	let points = ref 0 in
	let oro = ref 0 in
	Array.iter (fun carte -> 
		(match carte.valeur with
		| Roi | Dame | Cavalier -> valeur_totale := !valeur_totale + 10
		| Sept -> (match carte.couleur with | Or -> incr points |_ -> ()); valeur_totale := !valeur_totale + 7; incr sette
		| Nombre(a) -> valeur_totale := !valeur_totale + a);

		(match carte.couleur with | Or -> incr oro |_ -> ());

		if carte.upside then incr points;

		) pile ;
	if !sette >= 3 then incr points;
	(!points, !valeur_totale, !oro);;
	

let gagnant (jeux: (int*int*int) array ): int = 
	let max_ind_valeur = ref 0 in
	let max_ind_oro = ref 0 in
	let points = Array.make (Array.length jeux) 0 in
	Array.iteri (fun i pile -> (match pile with
	| (pts, valeur_tot, oro) -> 
	(if valeur_tot > (match jeux.(!max_ind_valeur) with | (_, tot, _) -> tot) then 
	max_ind_valeur := i);
	(if oro > (match jeux.(!max_ind_oro) with | (_, _, oro_other) -> oro_other) then 
	max_ind_oro := i);
	points.(i) <- pts)
	) jeux;
	points.(!max_ind_valeur) <- points.(!max_ind_valeur) + 1;
	points.(!max_ind_oro) <- points.(!max_ind_oro) + 1;
	let gagnant = ref 0 in
	(*Array.fold_left (fun acc el -> if points.(el) > points.(acc) then el else acc) 0 points;;*)
	Array.iteri (fun i el -> if el > points.(!gagnant) then gagnant := i) points;
	!gagnant;;
	
let joueur1 = [|
  {valeur = Sept ; couleur = Or; upside = false}; 
  {valeur = Roi ; couleur = Vase; upside = false}; 
  {valeur = Nombre 5 ; couleur = Epee; upside = true};
  {valeur = Dame ; couleur = Massue; upside = false};
  {valeur = Nombre 2 ; couleur = Or; upside = false}
|];;

let joueur2 = [|
  {valeur = Cavalier ; couleur = Massue; upside = true}; 
  {valeur = Nombre 4 ; couleur = Epee; upside = true};
  {valeur = Nombre 6 ; couleur = Vase; upside = false};
  {valeur = Sept ; couleur = Massue; upside = false};
  {valeur = Nombre 3 ; couleur = Or; upside = false}
|];;

let valeur_joueur1 = valeur_pile joueur1;;
let valeur_joueur2 = valeur_pile joueur2;;


let resultat = [|valeur_joueur1; valeur_joueur2|];;

let gagnant_partie = gagnant resultat;;
