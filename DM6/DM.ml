



let tables n = if n <= 6 then failwith "sale fils d'option si" else match n mod 4 with
	| a when a = 0 -> (n/4, 0)
	| a when a = 1 -> (n/4 + 1, -1)
	| a when a = 2 -> (n/4 + 2, -2)
	| a when a = 3 -> (n/4, 1);;



let minecart tab = let min = ref tab.(0) in let abs a = if a < 0 then -a else a in
	Array.iteri (fun i el -> if abs(el - i) < !min then min := abs(el - i)) tab;
	!min;;


minecart [|4;5;19|];;



let premiercommepremier arr = let num = ref (-1) in
	Array.iteri (fun i el -> if el = arr.(0) && !num = -1 then num := i) arr;
	!num;;


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




let equilibre tab = let tbl = Hashtbl.create in
	Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
		| [] -> 0
		| a -> a + 1)) tab;
	let (a, b) = Hashtbl.fold (fun _ va prev_vals -> match prev_vals with 
	| (a, b) -> if va > a then (va, b) else if va < b then (a, va) else (a, b))
	 tbl (tab.(0), tab.(0)) in a = b;; (* NE MARCHE PAS ! *)









is_prime 223;;
	


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
	else (if copy mod prime = 0 then decomp (prime::liste) (copy / prime) prime
				else decomp liste copy (get_next_prime prime));;



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


	let decomp2 n = let rec aux liste copy prime prev = 
		if copy = 1 then liste
		else (
			if copy mod prime = 0 then aux 
			(if prev then (match liste with
			| (p, n)::q -> (p, n+1)) (* NE TOURNE PAS *)
			else (prime, 1)
			)::liste) (copy / prime) prime true
			else aux liste copy (get_next_prime prime) false
		)
		in aux [] n 2;;
	
	decomp2 295;;
	

	let decomp2 n = let rec aux liste copy prime = 
		if copy = 1 then liste
		else
		begin
			if copy mod prime = 0 then match liste with
			| (p, n)::q when p = prime -> aux ((p, n+1)::q) (copy/prime) prime (* MARCHE !*)
			| _ -> aux ((prime, 1)::liste) (copy / prime) prime
			else aux liste copy (get_next_prime prime)
		end
		in aux [] n 2;;
	
