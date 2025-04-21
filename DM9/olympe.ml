(*Ex 80*)
let rec gcd a b = 
  if b = 0 then a
  else gcd b (a mod b);;

let rec ppcm_ens l = match l with
  |[] -> 0
  |[a] -> a
  |a::b::r -> ppcm (((a*b)/(gcd a b))::r);;

let x = [1; 4; 10; 7; 12; 3];;

ppcm x;;

(* Ex 81 *)
let rec subsetsum l x = match l with
  |[] -> x = 0
  |a::r -> subsetsum r x || subsetsum r (x-a);;

subsetsum x 17;;
subsetsum x 41;; 

(*Ex 82*)
let selectfrom t n = 
  let lg = Array.length t in
  if lg = 0 then [||]
  else let tun = Array.length t.(0) in Array.iter (fun i -> if Array.length i <> tun then failwith "faut croire que la taille compte des fois") t;
    Array.iter(fun i -> if i < 0 || i >= tun then failwith "la taille doit vraiment compter") n;
    Array.init lg (fun i -> t.(i).(n.(i)));;

let t = [| [|1; 2; 3|]; [|4; 5; 6|]; [|7; 8; 9|] |];;
selectfrom t [|0; 1; 2|];;

(* Ex 83*)
type arbre = Noeud of arbre list

let rec strahler (Noeud enfants) =
  match enfants with
  | [] -> 1 
  | _ -> let ind = List.map strahler enfants in
      let max_ind = List.fold_left max 0 ind in
      let freq = List.fold_left (fun acc x -> if x = max_ind then acc + 1 else acc) 0 ind in
      if freq >= 2 then max_ind + 1 else max_ind;;

let arabre =
  Noeud [
    Noeud [];
    Noeud [
      Noeud [];
      Noeud []
    ]
  ];;

strahler arabre;;

(* Ex 84 *)
type graphe1 = { mutable sommets : int list; mutable arcs : (int * int) list; };;

let dist_n go s n = 
  if not(List.exists (fun i -> i = s) go.sommets) then failwith "a pas sommets";
  let voisins som = List.fold_left (fun acc (src, dst) -> if src = som then dst :: acc else acc ) [] go.arcs in
  let rec aux so en =
    if en = 0 then so
    else let next = List.flatten (List.map voisins so) in 
      aux (List.sort_uniq compare next) (en - 1) 
  in aux [s] n;; 

let g = {
  sommets = [0; 1; 2; 3; 6; 7; 9];
  arcs = [ (0,1); (0,2); (0,6); (1,2); (2,0); (2,7); (2,3); (3,9); (6,7); (6,9); (7,0); (7,9)]
};;

dist_n g 0 2;;
dist_n g 8 3;;
dist_n g 9 10;;