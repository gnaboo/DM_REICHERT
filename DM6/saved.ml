

let tables n = if n <= 6 then failwith "je t'emmerde" else match n mod 4 with
	| a when a = 0 -> (n/4, 0)
	| a when a = 1 -> (n/4 + 1, -1)
	| a when a = 2 -> (n/4 + 2, -2)
	| a when a = 3 -> (n/4, 1);;
	

	
let premiercommepremier arr = let num = ref (-1) in
	Array.iteri (fun i el -> if el = arr.(0) && !num = -1 then num := i) arr;
	!num;;

let premiercommeavant arr = let ret = ref (-1, -1) in
	let prev = Array.make 	;;
	

let is_prime num = if num mod 2 = 0 then num = 2
	else begin
	let rec aux counter = 
	if num = counter then true
	else (num mod counter <> 0) && aux (counter+2)
	in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
	end;;

is_prime 223;;
	
let get_next_prime n = let next = ref (n+1) in
	while not (is_prime !next) do
		incr next;
	done;
	!next;;

let decomp n = let arr = Array.make (n/2) 1 in (* encore une fois, optimisable *)
	let ind = ref 0 in (* plus pratique d'utiliser des listes... *)
	let copy = ref n in
	let prime = ref 2 in
	while !copy <> 1 do
		if !copy mod !prime = 0 then 
		begin
			arr.(!ind) <- !prime;
			incr ind;
			copy := !copy / !prime;
		end
		else prime := (get_next_prime !prime);
	done;
	arr;;

decomp 7;;

let premierabsent tab = let max = Array.fold_left max 0 tab in
	(max*(max+1))/2 - Array.fold_left (+) 0 tab;; (* en fonction de l'interprétation de l'énoncé *)

let premierabsentbis tab = let b = Array.sort tab in
	let a = ref (-1) in
	for i = 0 to ((Array.length b) -2) do
	if !a = -1 && arr.(i) + 1 <> arr.(i+1) then a := arr.(i)+1
	done;
	!a;



premierabsent [|1;7;5;3;2|];;





let decomp n = let arr = Array.make (n/2) 1 in (* encore une fois, optimisable *)
	let get_next_prime n = let next = ref (n+1) in 
		let is_prime num = if num mod 2 = 0 then num = 2
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
	let ind = ref 0 in (* plus pratique d'utiliser des listes... *)
	let copy = ref n in
	let prime = ref 2 in
	while !copy <> 1 do
		if !copy mod !prime = 0 then 
		begin
			arr.(!ind) <- !prime;
			incr ind;
			copy := !copy / !prime;
		end
		else prime := (get_next_prime !prime);
	done;
	arr;;

decomp 7;;


	let is_prime num = if num mod 2 = 0 then num = 2
	else begin
	let rec aux counter = 
	if num = counter then true
	else (num mod counter <> 0) && aux (counter+2)
	in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
	end;;

is_prime 223;;
	
let get_next_prime n = let next = ref (n+1) in
	while not (is_prime !next) do
		incr next;
	done;
	!next;;
	
let decomp n = let rec aux liste copy prime = 
	if copy = 1 then liste
	else 
	begin
		if copy mod prime = 0 then aux (prime::liste) (copy / prime) prime
		else aux liste copy (get_next_prime prime)
	end
	in aux [] n 2;;

decomp 295;;



let decomp2 n = let rec aux liste copy prime = 
	if copy = 1 then liste
	else
	begin
		if copy mod prime = 0 then match liste with
		| (p, n)::q when p = prime -> aux ((p, n+1)::q) (copy/prime) prime
		| _ -> aux ((prime, 1)::liste) (copy / prime) prime
		else aux liste copy (get_next_prime prime)
	end
	in aux [] n 2;;

decomp2 345983;;

let rec pow a = function
  | 0 -> 1
  | 1 -> a
  | n -> 
    let b = pow a (n / 2) in
    b * b * (if n mod 2 = 0 then 1 else a);;

List.fold_left (fun acc el -> match el with | (a, b) -> (pow a b)*acc) 1 (decomp2 10);;

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

decomp 21474837;;


let equilibre tab = let tbl = Hashtbl.create 0 in
	Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
		| None -> 0
		| Some(a) -> a + 1)) tab;
	let first = Hashtbl.find tbl tab.(0) in
	Hashtbl.fold (fun _ valeur acc -> valeur = first 
	let arr = Array.make (Hashtbl.length tbl) 0 in
	let ind = ref 0 in
	Hashtbl.iter (fun valu -> arr.(!ind) <- valu; incr ind) tbl;
	Array.fold_left ( = ) (arr.(0)) arr;;
	
	



