(* Utils *)
let abs x = if x < 0 then -x else x;;

let print_float_array (a: float array): unit =
	Array.iter (fun x -> Printf.printf "%f " x) a;
	Printf.printf "\n"
;;

(* Exercice 50 *)
let tables (n: int): (int * int) =
    let rec aux b =
        if b > 3 then (-1, -1)
        else
            let t = n - 3 * b in
            if t mod 4 = 0 then (t / 4, b) else aux (b + 1)
	in aux 0
;;

(* Exercice 51 *)
let q1 (a: 'a array): 'a array =
	let size = Array.length a in
		if size mod 4 <> 1 then failwith "Array size must be 4n + 1"
		else Array.init ((size - 1) / 4) (fun i -> a.(i))
;;

(* Exercice 52 *)
let minecart (table: int array): int =
	let size = Array.length table in
	let gap = ref (abs (table.(0) - 0)) in
		for i = 1 to size - 1 do
			let g = abs (table.(i) - i) in
			if g < !gap then gap := g
		done;
	!gap
;;

(* Exercice 53 *)
let premiercommepremier (table: 'a array): int =
	let num = ref (-1) in 
		Array.iteri (fun i e -> if i <> 0 && e = table.(0) && !num = -1 then num := i) table;
	!num
;;

(* Exercice 54 *)
let premiercommeavant (table: int array): (int * int) =
	let res = ref (-1, -1) in
		for i = 1 to Array.length table - 1 do
			if table.(i) = table.(i - 1) && fst !res = -1 then res := (i, i - 1)
		done;
	!res
;;

(* Exercice 55 *)
(* let equilibre (table: int array): bool = *)
	(* Gabriel l'a déjà fait :p *)

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
let decomp (n: int) : (int * int) list =
	let rec count x d c =
		if x mod d = 0 then count (x / d) d (c + 1) else (x, c)
	in let rec aux n i acc =
		if i * i > n then
			if n > 1 then (n, 1) :: acc else acc
		else if n mod i = 0 then
			let (new_n, pow) = count n i 0 in aux new_n i ((i, pow) :: acc)
		else aux n (i + 2) acc
	in let acc = [] in
		let (new_n, pow) = count n 2 0
		in let acc2 = if pow > 0 then [(2, pow)] else acc
	in List.rev (aux new_n 3 acc2)
;;

(* Tests *)
let () =
	(* Exercice 50 *)
	let res = tables 9 in
	Printf.printf "Exercice 50 : %d %d\n" (fst res) (snd res);

	(* Exercice 51 *)
	let t = [|1.; 2.; 3.; 4.; 5.; 6.; 7.; 8.; 9.; 1.0; 1.1; 1.2; 1.3 |] in
	Printf.printf "Exercice 51 : "; print_float_array (q1 t);

	(* Exercice 52 *)
	let t = Array.init 13 (fun i -> i + 1) in
	Printf.printf "Exercice 52 : %d\n" (minecart t);

	(* Exercice 53 *)
	let t = [| 1; 2; 3; 1; 2; 4; 1; 2; 3; 1; 2 |] in
	Printf.printf "Exercice 53 : %d\n" (premiercommepremier t);

	(* Exercice 54 *)
	let t = [| 1; 2; 3; 2; 42; 42; 8; 8 |] in let res = premiercommeavant t in
	Printf.printf "Exercice 54 : %d %d\n" (fst res) (snd res);

	(* Exercice 55 *)
	(* * *)
	Printf.printf "Exercice 55 : ~\n";

	(* Exercice 56 *)
	Printf.printf "Exercice 56 : %d\n" (premierabsent t);

	(* Exercice 57 *)
	Printf.printf "Exercice 57 : %d\n" (rpz "moselle elle somme lol es 42 = 57");

	(* Exercice 58 *)
	let res = decomp 42 in Printf.printf "Exercice 58 : ";
	List.iter (fun (a, b) -> Printf.printf "(%d, %d) " a b) res;
	Printf.printf "\n"
;;
