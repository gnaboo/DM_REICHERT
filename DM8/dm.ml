


let find_dom_ind pol prev_dom_ind = 
  (* rajouter un failsafe ! *)
  let dom_ind = ref prev_dom_ind in
  while pol.(!dom_ind) = 0. && !dom_ind > 0 do
    decr dom_ind; 
  done;
  !dom_ind;;


let diveucl (num: float array) (denom: float array) : (float array) = 
  (* vérifier que dom denom <> 0 *)
  let num_copy = Array.copy num in
  let n = Array.length num in
  let m = Array.length denom in 
  
  let pol = Array.make n (0.) in 
  
  let dom_ind_num = ref (find_dom_ind num_copy (n-1)) in
  let dom_ind_denom = find_dom_ind denom (m-1) in 
  let dom_denom = denom.(dom_ind_denom) in 
  
  
  if dom_denom = 0. then failwith "Division par polynome nul"
  else
  
    let counter = ref n in
  
    while m <= !dom_ind_num && !counter > 0 do
    
      decr counter;
    
      let dom_nom = num_copy.(!dom_ind_num) in 
      let coef = dom_nom /. dom_denom in
      let x_factor = !dom_ind_num - dom_ind_denom in
    
      (*Printf.printf "%f\n" dom_nom;
       Printf.printf "%f\n" dom_denom;
       Printf.printf "%d\n" !dom_ind_num;
       Printf.printf "%d\n" dom_ind_denom;
       Printf.printf "%f\n" coef;
       Printf.printf "%d\n" x_factor;
       Array.iter (fun i -> Printf.printf "%f," i) pol; Printf.printf "\n"; *)
      pol.(!dom_ind_num) <- coef;
    
      for i = x_factor to !dom_ind_num do
        num_copy.(i) <- num_copy.(i) -. (coef *. denom.(i-x_factor));
      done;
    
      (*Array.iter (fun i -> Printf.printf "%f," i) num_copy; Printf.printf "\n"; *)
    
      dom_ind_num := (find_dom_ind num_copy !dom_ind_num); 
    
    done;
    pol;;


diveucl [|0.;1.;4.;2.|] [|1.|];;
diveucl [|0.;1.;4.;2.;0.;0.|] [|0.;0.;1.|];;
diveucl [|0.;1.;4.;2.;0.;0.|] [|0.;0.;0.|];;


type nombre = PlusInfini | MoinsInfini | Valeur of int;;

let nombrediviseurs n = 
  if n = 0 then PlusInfini
  else 
    (
      let ctr = ref 0 in 
      for i = 0 to n do
        if n mod i = 0 then incr ctr
      done;
      Valeur(!ctr);
    )
;;


let ptm (n: int) : (string) = (* j'avais pas lu la consigne, j'ai découvert à la fin qu'il fallait renvoyer une liste *)
  let rec aux (ctr: int) (suite: int array) : (int array) = 
    if ctr >= n then suite
    else 
      (
        let size = Array.length suite in
        let cop = Array.make (size * 2) 0 in
        Array.iteri (fun i el -> cop.(i) <- el) suite;
        for i = 0 to size-1 do
          cop.(i + size) <- 1-cop.(i);
        done;
        aux (ctr+1) (cop);
      )
  in Array.fold_left (fun acc el -> acc ^ (string_of_int el)) "" (aux 0 [|0;1|]);; 
    


let rec fact n = if n = 0 then 1 else n * fact (n-1);;

let zerofact n = let value = int_of_float(log(float_of_int(n))) / int_of_float(log(5.)) in
  let ctr = ref 0 in
  let pow = ref 1 in
  for i = 0 to value do
    ctr := !ctr + (n / !pow); (* marche pas *)
    pow := !pow * 5;
  done; 

  for i = 0 to 10 do
    Printf.printf "fact:%d\n" (fact i);
    Printf.printf "zero:%d\n" (fact i);
  done;
;;

let zerofact2 n = 
  let ctr = ref 0 in
  let n_bis = ref n in
  while (!n_bis / 5) > 0 do
    ctr := !ctr + (!n_bis / 5);
    n_bis := !n_bis / 5;
  done;
  !ctr;;

let test =   
  for i = 0 to 10 do 
    Printf.printf "%d! = fact:%d | zero:%d\n" i (fact i) (zerofact2 i);
  done;
  ();;


(*
  type note = Do | Re | Mi | Fa | Sol | La | Mi | Si;;
  type alt = Rien | Bemol | Diese;;

  let is_digit = function '0' .. '9' -> true | _ -> false;; (* merci stackoverflow *)

  let parse_notes str = 
    let alt = ref Rien in
    let note = 
      if String.starts_with "sol" str then (
        if not is_digit (str.(2)) then alt := match str.(2) with | "d" -> Diese | "b" -> Bemol;
            Sol
      )
      else
        match str.(0), str.(1) with
        | "d","o" -> Do
        | "r","e" -> Re
        | "m","i" -> Mi
        | "f","a" -> Fa
        | "l","a" -> La
        | "s","i" -> Si in
    let alt = ();;
          
      
    
  let sep = ref 1 in
  while not(is_digit (string.(!sep)) || string.(!sep) = 'd' || string.(!sep) = 'b') do
    incr sep;
  done; 
  ;;
  
  


  
  *)








