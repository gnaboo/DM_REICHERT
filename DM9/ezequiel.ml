(* Utils *)
let string_of_int_list (l: int list): string =
  String.concat ", " (List.map string_of_int l)
;;

let print_matrix (matrix: 'a array array): unit =
  Array.iter (fun row ->
    Printf.printf "[| ";
    Array.iter (Printf.printf "%d ") row;
    Printf.printf "|]\n"
  ) matrix
;;

(* Exercice  *)
let ppcm_ens (seq: int list): int =
  let rec pgcd a b = match b with
    | 0 -> a
    | _ -> pgcd b (a mod b)
  in let ppcm a b = a * b / (pgcd a b) in
  let rec aux acc seq = match seq with
    | [] -> acc
    | x::q -> aux (ppcm acc x) q
  in aux 1 seq
;;

(* Exercice 81 *)
let subsetsum (seq: int array) (target: int): bool =
  let size_pow2 = 1 lsl (Array.length seq) in
  let sums = Hashtbl.create size_pow2 in
  for i = 0 to size_pow2 - 1 do
    let sum = ref 0 in
    let pow2 = ref 1 in
    for j = 0 to Array.length seq - 1 do
      if ((i / !pow2) mod 2) = 1 then
        sum := !sum + seq.(j);
      pow2 := !pow2 * 2;
    done;
    (* add the sum to the hashtable *)
    Hashtbl.add sums !sum true
  done;
  (* check if the target is in the hashtable *)
  Hashtbl.mem sums target
;;

(* Exercice 82 *)
let selectfrom (matrix: 'a array array) (indexes: int array) : 'a array array =
  let rows = Array.length matrix in
  let cols = Array.length indexes in
  let result = Array.make_matrix rows cols (matrix.(0).(0)) in
  for i = 0 to rows - 1 do
    for j = 0 to cols - 1 do
      let index = indexes.(j) in
      if index < Array.length matrix.(i) then
        result.(i).(j) <- matrix.(i).(index)
      else
        failwith "Index out of bounds"
    done
  done;
  result
;;

(* Exercice 83 *)
type tree = Empty | Node of tree list ;;

let rec strahler (t: tree): int = match t with
  | Empty -> 0
  | Node [] -> 1
  | Node children ->
      let child_values = List.map strahler children in
      let max_val = List.fold_left max 0 child_values in
      let count_max = List.fold_left (fun acc x -> if x = max_val then acc + 1 else acc) 0 child_values in
      max_val + (if count_max > 1 then 1 else 0)
;;

(* Exercice 84 *)
(* Non *)


(* Main tests *)
let () =
  (* Exercice 80 *)
  let seq80 = [2; 3; 4; 5] in
  Printf.printf "Exercice 80 : Le PPCM de %s est %d\n\n"
    (string_of_int_list seq80) (ppcm_ens seq80);

  (* Exercice 81 *)
  let seq81 = [| 1; 2; 3; 4; 5 |] in
  let res81 = subsetsum seq81 6 in
  Printf.printf "Exercice 81 : La somme %d est-elle dans le tableau ? %b\n\n" 6 res81;

  (* Exercice 82 *)
  let matrix82 = [| [| 1; 2; 3 |]; [| 4; 5; 6 |]; [| 7; 8; 9 |] |] in
  let indexes82 = [| 2; 0 |] in
  let result82 = selectfrom matrix82 indexes82 in
  Printf.printf "Exercice 82  :La matrice \"sélectionnée\" est :\n";
  print_matrix result82;
  print_newline ();

  (* Exercice 83 *)
  let tree83_1 = Node [Empty; Empty; Empty] in
  let tree83_2 = Node [Node []; Node [Empty; Node []]] in
  let tree83_3 = Node [Node []; Node [Node []]] in
    Printf.printf "Exercice 83 : La nombre de strahler de l'arbre 1 est %d\n"
      (strahler tree83_1);
    Printf.printf "Exercice 83 : La nombre de strahler de l'arbre 2 est %d\n"
      (strahler tree83_2);
    Printf.printf "Exercice 83 : La nombre de strahler de l'arbre 3 est %d\n"
      (strahler tree83_3)

  (* Exercice 84 *)
;;
