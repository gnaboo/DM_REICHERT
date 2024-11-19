

type t = bool = 
|false
|true


let rec display_list l = match l with
	| [] -> 0;
	| a::q -> print_int a; print_string ", " ; display_list q
	| _ -> 0;;


let plusetfois a b = [a+b;a*b];;
plusetfois 2 5;;
display_list (plusetfois 2 5);;


let rec power a b = match b with
	| n_b -> if b > 0 then a * power a (n_b-1) else 1;;
	
power 2 5;;

let ppp2 a = let rec comp a b = if b >= a then b else comp a (b*2) 
	in comp a 1;;	
	
ppp2 1;;
ppp2 2147483649;;

(*let rec power a b = if a > 2**;;*)

(*let leeloo l = match l with
	|a::b::c::d::e::q -> e
	|a::b::c::d::e -> e.(0)
	|_ -> 0;

leeloo [1;2;3;4;5] 5;;
*)

let leeloo l = let rec get_element l b = match l with 
	| [] -> failwith "La liste ne contient pas 5 éléments"
	| a::q -> if b = 5 then a else get_element q (b+1)
	in get_element l 1;;
	
leeloo [1;2;3;4];;
leeloo [1;2;3;4;5];;
leeloo [1;2;3;4;6;7];;

let coupe l = let rec aux l ol_1 ol_2 b = match l with
	| [] -> (ol_1, ol_2)
	| a::q -> if b mod 2 = 0 then aux q (ol_1@[a]) ol_2 (b+1)
				 else aux q ol_1 (ol_2@[a]) (b+1) in aux l [] [] 0;;
			 
coupe [1;2;3;4;5];;

(*let colle l o_l = let rec aux l o_l l_f b = match l with
	| a::q when b = let rec count l = match l with
		| [] -> 0
		| a::q -> 1 + count q
	in count l + count o_l -> l_f
	| a::q when b mod 2 = 0 -> aux q o_l (l_f@[a]) (b+1)
	| _ -> match o_l with
		| a::q -> aux l q (l_f@[a]) (b+1)
	in aux l o_l [] 0;;*)

let colle l o_l = let rec aux l o_l l_f b = match l with
	| [] when o_l = [] -> l_f
	| a::q when b mod 2 = 0 -> aux q o_l (l_f@[a]) (b+1)
	| _ -> match o_l with
		| a::q -> aux l q (l_f@[a]) (b+1)
	in aux l o_l [] 0;;


colle [1;2;3] [4;5;6];;


let rec compte l el = let rec counter l c = match l with
	| [] -> c
	| b::q -> if b = el then counter q (c+1) else counter q c
	in counter l 0;;
	
compte [1;2;3;4;4;2;1] 0;;





let sommesi l func = let rec eval l c = match l with
	| [] -> c
	| a::q -> if func (a) then eval q (a+c) else eval q c
	in eval l 0;;

let pos a = a >= 0;;
let test_bool b = if b then "true" else "false";;
test_bool (pos 1);;
test_bool (pos (-1));;
sommesi [1;2;3;-1;-3; -1876] (pos);;



let majopred l func = let rec intern l balance = match l with
	| [] -> balance
	| a::q -> if func a then intern q (balance+1) else intern q (balance-1)
	in if intern l 0 >= let rec size l c = match l with
		| [] -> 0
		| a::q -> c+size q c in size l 0 / 2 then true else false;;

let pos a = a >= 0;;
let test_bool b = if b then "true" else "false";;
test_bool (pos 1);;
test_bool (pos (-1));;
majopred [1;2;3;-1;-3; -1876] (pos);;
majopred [1;2;3;-1;-3;-2;-1] (pos);;

let rec lexico l o_l = let rec get_element l b el = match l with 
	| [] -> failwith "Fond de liste"
	| a::q -> if b = el then a else get_element q (b+1) el
	in let rec aux l o_l c = match l with
	| [] when o_l = [] -> failwith "Les deux listes sont vides"
	| [] -> true
	| a::q -> try get_element o_l 1 c with
		| b -> if a > b then false else aux l o_l (c+1)
		| _ -> false 
	in aux l o_l 1;;
	
let lexico l o_l = let rec aux l o_l c = match l with
	| [] when o_l = [] -> failwith "Les deux listes sont vides"
	| [] -> true
	| a::q -> match o_l with
		| [] -> false
		| b::s -> if a > b then true else aux l s;;
		
let rec lexico l o_l = match l with
	| [] when o_l = [] -> failwith "Les deux listes sont vides"
	| [] -> true
	| a::q -> match o_l with
		| [] -> false
		| b::s -> if a < b then true
					 else if a > b then false 
					 else lexico q s;;
	
lexico [1;2;3] [1;2;3;4;5];;




let aplatir l = let rec aux l n_l = match l with
	| [] -> n_l
	| a::q -> aux q (n_l@a)
	in aux l [];;
aplatir [[1;2;3;4];[5;6;7];[8;9;10;11];[12]];;


let aplatir l = 
	let rec copier l o_l = match o_l with
		| [] -> l
		| a::q -> copier (l::a) q
	in 
	let rec iter l a = match l with
	| [] -> l
	| a::q -> copier a
	
	in match l with = 
	| [] -> []
	| a -> iter l;;
	

let rec aplatir l = match l with
	| [] -> ()
	| a::q -> ( a @ (aplatir q));;
	
aplatir [[1;2;3;4];[5;6;7];[8;9;10;11];[12]];;
	

let rec append l a = match l with
	| [] -> [a]
	| b::q -> b::append q a;;
	
append ([1;2;3]) (5);;

let add_list l o_l = 
	let rec intern l o_l c = match o_l with
		| [] -> []
		| a::q when c = 1 -> (append l a)@intern l q 2 (*@(intern l q 2)*)
		| a::q -> append (intern l q 2) a;
	in intern l o_l 1;;
	
	
add_list [1;2;3] [4;5;6];;

[1;2;3]@[4;5;6];;





	
let rec copier l o_l = match o_l with
		| [] -> l
		| a::q -> a::append l 
		
		
		
copier [1;2;3;4;] [1;2;3];;

















	
	
	
