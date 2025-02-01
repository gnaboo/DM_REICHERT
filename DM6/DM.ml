
let abs a = if a < 0 then -a else a;;

let minecart tab = let min = ref tab.(0) in
	Array.iteri (fun i el -> if abs(el - i) < !min then min := abs(el - i)) tab;
	!min;;
	
minecart [|4;5;19|];;


let equilibre tab = let tbl = Hashtbl.create in
	Array.iter (fun el -> Hashtbl.replace tbl el (match Hashtbl.find_opt tbl el with
		| [] -> 0
		| a -> a + 1)) tab;
	let (a, b) = Hashtbl.fold (fun _ va prev_vals -> match prev_vals with 
	| (a, b) -> if va > a then (va, b) else if va < b then (a, va) else (a, b))
	 tbl (tab.(0), tab.(0)) in a = b;; (* NE MARCHE PAS ! *)



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





