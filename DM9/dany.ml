(* QUARANTA DANY *)


(* Exercice 80 OUI *)
let ppcm_ens (sequence: int list) : int =
  let rec pgcd a b = match b with | 0 -> a | _ -> pgcd b (a mod b) in
  let ppcm a b = (a*b) / pgcd a b in
  let rec aux l = match l with
    | [] -> failwith "Séquence vide."
    | [x] -> x
    | [x; y] -> ppcm x y
    | x::q -> ppcm x (aux q)
  in aux sequence
;;

let main1() =
  print_int (ppcm_ens [6; 8; 15]); print_newline() (* 120 *)
;;


(* Exercice 81 OUI *)
let subsetsum (sequence: int list) (v: int) : bool =
  let memo = Hashtbl.create 8 in
  let rec aux i l sum = match l with
    | [] -> sum = v
    | x::q ->
      match Hashtbl.find_opt memo (i, sum) with
        | Some b -> b
        | None ->
          let sans = 
            match Hashtbl.find_opt memo (i+1, sum) with
            | None -> let b = aux (i+1) q sum in Hashtbl.add memo (i+1, sum) b; b
            | Some b -> b
          in
          let avec =
            match Hashtbl.find_opt memo (i+1, sum+x) with
            | None -> let b = aux (i+1) q (sum+x) in Hashtbl.add memo (i+1, sum+x) b; b
            | Some b -> b
          in
          let rep = sans || avec in Hashtbl.add memo (i+1, sum) rep; rep

  in aux 0 sequence 0
;;

let main2() =
  let b = subsetsum [-5; 4; 7; 5; 2] 8 in
  if b then print_string "OUI\n" else print_string "NON\n" (* OUI *)
;;


(* Exercice 82 NON *)
let selectfrom (sequence: 'a array array) (select: int array) : 'a array array =
  let n = Array.length sequence in
  let taille_select = Array.length select in

  let rep = Array.init (n) (fun _ -> Array.make (taille_select) sequence.(0).(0)) in
  for i=0 to n-1 do
    for j=0 to taille_select-1 do
      rep.(i).(j) <- sequence.(i).(select.(j))
    done
  done;
  rep
;;

let main3() =
  let sequence = [|[|1; 2; 3; 4|]; [|5; 6; 7; 8|]; [|9; 10; 11; 12|]|] in
  let select = [|2; 0; 3; 1|] in
  let result = selectfrom sequence select in

  print_string "Séquence :\n";
  Array.iter (fun x -> Array.iter (fun y -> print_int y; print_string " ") x; print_newline()) sequence;

  print_string "Réponse :\n";
  Array.iter (fun x -> Array.iter (fun y -> print_int y; print_string " ") x; print_newline()) result;
;;


(* Exercice 83 OUI *)
type arbre = Vide | Noeud of arbre list;;

let rec strahler (a: arbre) : int =
  match a with
    | Vide -> 0
    | Noeud(children) when children = [] -> 1
    | Noeud(children) ->
      let plus = ref false in
      let m = List.fold_left (fun m child -> let n = strahler child in if n > m then (plus := false; n) else if n = m then (plus := true; m) else m) (-1) children in
      if m = 0 then 1 else
      if !plus then m+1 else m
;;

let main4() =
  let a =
    Noeud [
      Noeud [Noeud []; Noeud []];
      Noeud [Noeud []; Noeud []]
    ]
in
  Printf.printf "%d\n" (strahler a) (* 3 *)
;;


(* Exercice 84 OUI *)
type graphe = (string * (string list)) list;;

let dist_n (g: graphe) (origine: string) (n: int) : string list =
  let rec mouline_sommet s etape rep =
    if etape = n then if not(List.mem s rep) then s::rep else rep else

    List.fold_left (fun acc (source, suivants) ->
      if source = s then List.fold_left (fun acc2 suivant -> mouline_sommet suivant (etape+1) acc2) acc suivants
      else acc
    ) rep g
  
  in mouline_sommet origine 0 [];
;;

let main5() =
  let g = [
    ("A", ["B"; "C"]);
    ("B", ["C"; "D"]);
    ("C", ["D"]);
    ("D", []);
  ]
in List.iter (fun s -> print_string s; print_string " ") (dist_n g "A" 2); print_newline()  (* D C *)
;;


(* Exercice 85 OUI *)
let mult (p1: float array) (p2: float array) : float array =
  let deg1, deg2 = Array.length p1 -1, Array.length p2 -1 in
  let rep = Array.make (deg1+deg2+1) 0.0 in

  for i=deg1 downto 0 do
    for j=deg2 downto 0 do
      rep.(i+j) <- rep.(i+j) +. p1.(i) *. p2.(j)
    done
  done;
  rep
;;

let unitaire (racines: float array) : float array =
  let n = Array.length racines in
  if n = 0 then failwith "Polynôme vide." else
  let rep = ref [|1.0|] in
  for i=0 to Array.length racines -1 do
    rep := mult !rep [|-.racines.(i); 1.0|]
  done;
  !rep
;;

let main6() =
  let racines = [|2.0; 1.0; 3.0; 8.0|] in
  let polynome = unitaire racines in
  Array.iter (fun x -> print_float x; print_string " ") polynome;
  print_newline()
;;


(* Exercice 86 OUI *)
let avggroupby (sequence: (string * float) list) : (string * float) list =
  let dict = Hashtbl.create 8 in
  let rec mouline l = match l with
    | [] -> Hashtbl.fold (fun s (sum, len) acc -> (s, sum/.len)::acc) dict []
    | (s, value)::q ->
      (match Hashtbl.find_opt dict s with
      | None -> Hashtbl.add dict s (value, 1.0)
      | Some (sum, len) -> Hashtbl.replace dict s (sum +. value, len +. 1.)); mouline q
  in mouline sequence
;;

let main7() =
  let data = [
    ("apple", 2.0); ("banana", 3.0); ("apple", 4.0); ("banana", 1.0);
    ("cherry", 5.0); ("apple", 6.0); ("banana", 2.0); ("cherry", 7.0);
    ("durian", 10.0); ("apple", 8.0); ("banana", 4.0); ("durian", 6.0);
    ("fig", 3.5); ("fig", 4.5); ("grape", 2.0); ("grape", 4.0); ("grape", 6.0);
    ("banana", 5.0); ("cherry", 6.0); ("durian", 4.0)
  ] in
  let rep = avggroupby data in
  List.iter (fun (s, v) -> Printf.printf "(%s, %f) " s v) rep; print_newline()
;;


(* Exercice 87 NON *)
let trouve (s: string) (n: int) : int * int =
  let htbl = Hashtbl.create 8 in
  let len = String.length s in
  let a, b = ref (-1), ref (-1) in

  for i=0 to len-1 do if i+n <= len then begin
    let sequence = String.sub s i n in
    match Hashtbl.find_opt htbl sequence with
      | None -> Hashtbl.add htbl sequence i
      | Some j -> (if !a = -1 || j < !a then (a := j; b := i))
  end done;
  (!a, !b)
;;

let facteurmax (s: string) : int * int =
  let inf, sup = ref 1, ref (String.length s) in
  let a, b = ref (-1), ref (-1) in
  while (!inf <= !sup) do
    let m = (!inf + !sup) / 2 in
    let temp_a, temp_b = trouve s m in
    if (temp_a = -1 && temp_b = -1) then sup := m-1
    else (inf := m+1; a := temp_a; b := temp_b)
  done;
  if !a = -1 && !b = -1 then failwith "Facteur non trouvé"
  else (!a, !b)
;;

let main8() =
  let (a, b) = facteurmax "aaatestliveblivetest" in
  Printf.printf "(%d, %d)\n" a b (* (3, 16) *)
;;


(* Exercice 88 NON *)


let main9() =
0
;;


(* Exercice 89 *)


let main10() =
0
;;


let main() =
    (* main1(); *)
    (* main2(); *)
    (* main3(); *)
    (* main4(); *)
    (* main5(); *)
    (* main6(); *)
    (* main7(); *)
    (* main8(); *)
    main9();
    (* main10(); *)
;;

main();;
