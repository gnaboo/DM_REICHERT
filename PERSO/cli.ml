



type memoire = { taille : int ; data : (string, string) Hashtbl.t };;

let create_memory n = { taille = n ; data  = Hashtbl.create };;

let read_memoire memoire index = Hashtbl.find_opt (memoire.data) index;;

let write_memoire memoire index element = Hashtbl.replace (memoire.data) index element;;

let size memoire = memoire.taille;




type file = { name : string; key : int }

let hachage str mod_val = let counter = ref 0 in 
String.iteri (fun i char -> counter := (!counter + (int_of_char (char)) * (i+1)) mod mod_val) str; 
!counter;; 

let create_file memoire name content = write_memoire memoire name content;;





type 'a 'b action = Memory_Read of int | Memory_Write of int * int | Display of 'a | Compute of 'b;;









