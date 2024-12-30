let print_float_array t =
    Array.iter (fun x -> print_float x ; print_string " ") t;;

(* Exercice 41 : *)
let tirette (t: int array): int =
    if Array.length(t) mod 2 <> 0 then failwith "Pas de taille paire" else
    let sum = ref 0 in
        for i = 0 to Array.length(t) / 2 - 1 do
            sum := !sum + t.(i) + t.(Array.length(t) - i - 1)
        done;
    !sum
;;

(* Exercice 43 : *)
let croissant t =
    let rec aux i =
        match t with
        | [||] | [|_|] -> true
        | _ -> i = Array.length(t) - 1 || (t.(i) <= t.(i + 1) && aux (i + 1))
    in aux 0 (* la pitite récursion terminale comme on aime *)
;;

(* Exercice 45 : *)
let psrn (t1: float array) (t2: float array): float array =
    if Array.length(t1) <> Array.length(t2) then
        failwith "Les tableaux n'ont pas la même taille"
    else let t i = t1.(i) *. t2.(i) in Array.init (Array.length(t1)) t
;;

(* Exercice 47 : *)
let plsci t =
    let i = ref 0 and max = ref 0 in
        for i1 = 0 to Array.length t - 1 do
            let i2 = ref i1 and max2 = ref 1 in
                while !i2 + 1 < Array.length t && t.(!i2) = t.(!i2 + 1) do
                    incr i2; incr max2
                done;
            if !max2 > !max then (max := !max2; i := !i2)
        done;
    (!i - !max, !max)
;;

(* Exercice 49 : *)
let dominant (s: string): string =
    let t = Array.make 256 0 in
        for i = 0 to String.length(s) - 1 do
            let c = Char.code(s.[i]) in
            t.(c) <- t.(c) + 1
        done;
    let max = ref 0 in
        for i = 0 to 255 do
            if t.(i) > t.(!max) then max := i
        done;
    String.make 1 (Char.chr(!max));;


(* Tests *)
let () =
    (* Exercice 41 : *)
    let t = [|1; 2; 3; 4; 5; 6|] in
    print_int (tirette t); print_newline();

    (* Exercice 43 : *)
    let t = [|1; 2; 3; 4; 5; 6|] in
    print_string (string_of_bool (croissant t)); print_newline();

    let t2 = [|1; 2; 3; 5; 4; 6|] in
    print_string (string_of_bool (croissant t2)); print_newline();

    (* Exercice 45 : *)
    (* Example: carrés de 1 à 6 *)
    let t1 = [|1.; 2.; 3.; 4.; 5.; 6.|] in
    let t2 = [|1.; 2.; 3.; 4.; 5.; 6.|] in
    let t = psrn t1 t2 in print_float_array t; print_newline();

    (* Exercice 47 : *)
    let t1 = [|1.; 2.; 2.; 3.; 3.; 3.; 4.; 4.; 4.; 4.; 5.; 5.; 5.; 5.; 5.|] in
    let (i, max) = plsci t1 in Printf.printf "Index: %d; Apparaîssant: %d\n fois" i max;

    let t2 = [|1.; 2.; 3.; 3.; 4.; 5.; 6.; 6.|] in
    let (i, max) = plsci t2 in print_int i; print_string " "; print_int max; print_newline();

    (* Exercice 49 : *)
    let s = "abracadabra" in
    print_string (dominant s); print_newline()
;;
