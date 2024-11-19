(* DEVOIR MAISON DE GABRIEL RINGEISEN--BIARDEAUD *)

let plusetfois a b = [a+b;a*b];;

plusetfois 2 5;;



let ppp2 a = let rec comp a b = if b >= a then b else comp a (b*2) 
	in comp a 1;;	
	
ppp2 1;;
ppp2 2147483649;;



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
sommesi [1;2;3;-1;-3; -1876] (pos);;



let majopred l func = let rec intern l balance = match l with
	| [] -> balance
	| a::q -> if func a then intern q (balance+1) else intern q (balance-1)
	in if intern l 0 >= let rec size l c = match l with
		| [] -> 0
		| a::q -> c+size q c in size l 0 / 2 then true else false;;

let pos a = a >= 0;;
majopred [1;2;3;-1;-3; -1876] (pos);;
majopred [1;2;3;-1;-3;-2;-1] (pos);;


		
let rec lexico l o_l = match l with
	| [] when o_l = [] -> failwith "Les deux listes sont vides"
	| [] -> true
	| a::q -> match o_l with
		| [] -> false
		| b::s -> if a < b then true
					 else if a > b then false 
					 else lexico q s;;
	
lexico [1;2;4] [1;2;3;4;5];;



let aplatir l = let rec aux l n_l = match l with
	| [] -> n_l
	| a::q -> aux q (n_l@a)
	in aux l [];;

aplatir [[1;2;3;4];[5;6;7];[8;9;10;11];[12]];;



