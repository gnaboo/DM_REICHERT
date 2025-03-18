(* Types *)
type 'a tree = Empty | Node of 'a * 'a tree list;;

(* Exercice 73 *)
let nombrediviseurs (n: int): int =
  if n < 1 then 0 else if n = 1 then 1 else
    let count = ref 0 in
      let sqrt_n = Float.to_int (Float.sqrt (Float.of_int n)) in
      for i = 1 to sqrt_n do
        if n mod i = 0 then begin
          incr count;
          if i <> n / i then incr count;
        end;
      done;
    ;
  !count;
;;

(* Exercice 75 *)
let ptm (n: int): string =
  if n < 0 then invalid_arg "Invalid number" else
    "test..."
;;

(* Exercice 76 *)
let zerosfact (n: int): int =
  let rec aux (i: int): int =
    if n < i then 0 else n / i + aux (i * 5)
  in aux 5
;;

(* Exercice 77 *)
let rec hauteurarbre (t: 'a tree): int = match t with
  | Empty -> 0
  | Node (_, []) -> 1
  | Node (_, l) -> 1 + List.fold_left (fun acc e -> max acc (hauteurarbre e)) 0 l
;;

let () =
  (* Exercice 73 *)
  let res73 = [ 0; 1; 25; 3; 6; 42 ] in
  List.iter (fun e -> Printf.printf "Exercice 73 : %d\n" (nombrediviseurs e)) res73 ;;

  Printf.printf "\n" ;;

  (* Exercice 75 *)
  let res75 = List.init 8 (fun i -> i) in
  List.iter (fun e -> Printf.printf "Exercice 75 : %s\n" (ptm e)) res75 ;;

  Printf.printf "\n" ;;

  (* Exercice 76 *)
  let res76 = [ 3; 5; 10; 100; 1000 ] in
  List.iter (fun e -> Printf.printf "Exercice 76 : %d\n" (zerosfact e)) res76 ;;

  Printf.printf "\n" ;;

  (* Exercice 77 *)
  let res77 = [
    Empty;
    Node (1, [Node (2, [Node (3, [])]); Node (4, [Node (5, []); Node (6, [])])]);
    Node (2, [Node (3, [])]);
    Node (5, [])
  ] in List.iter (fun e -> Printf.printf "Exercice 77 : %d\n" (hauteurarbre e)) res77
;;
