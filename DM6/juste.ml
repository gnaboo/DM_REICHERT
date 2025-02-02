(* Exercice 52 *)
let minecart (tab: int array): int = 
	if Array.length tab = 0 then failwith "Tableau aussi remplit que le cerveau d'un ecg" else
	let abs a = if a < 0 then -a else a in let min = ref (abs (tab.(0))) in 
	Array.iteri (fun i el -> if abs(el - i) < !min then min := abs(el - i)) tab;
	!min;;

(* Exercice 55 | L'enfer *)
let equilibre tab = if Array.length tab = 0 then true;
let tbl = Hashtbl.create (Array.length tab) in
Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
  | None -> 1
  | Some(a) -> a + 1)) tab;
let first = Hashtbl.find tbl tab.(0) in
let arr = Array.make (Hashtbl.length tbl) 0 in
let ind = ref 0 in
Hashtbl.iter (fun _ valeur -> arr.(!ind) <- (valeur - first); incr ind) tbl;
Array.fold_left (fun acc valeur -> acc && (valeur = 0)) true arr;;


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
