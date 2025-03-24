  
  
  
type fraction = { nom: int; denom: int;};;


let simplifiable tab = (* O(n^2) si jamais on fait chaque fraction avec celle d'après... *)
	let is_same x1 x2 y1 y2 = x1*y2 = y1*x2 in
	(* 
	\forall (x, y, x', y') \in \mathbb{Z}^4\\
	\frac{x}{y} = \frac{x'}{y'} \Longleftrightarrow xy' = yx'
	*)
	
	let result = ref false in
	for i = 0 to (Array.length tab -1) do
		if not !result then
		begin		
		for y = (i+1) to (Array.length tab -1) do
			result := is_same (tab.(i).nom) (tab.(y).nom) (tab.(i).denom) (tab.(y).denom)
		done;
		end
	done;
	!result;;
	
let miroirlc = List.fold_left (fun acc i -> i::acc ) [];;

miroirlc [1;2;3;4];;

Array.map (fun a -> true) [||];;


let niederschaeffolsheim str =
  let compteur = ref 0 in
  let maxi = ref 0 in
  String.iter (fun el -> 
    if el = ' ' then (
      if !compteur <> 0 then (
        if !compteur > !maxi then maxi := !compteur;
        compteur := 0
      )
    ) else 
      incr compteur
  ) str;
  
  if !compteur > !maxi then maxi := !compteur;
  !maxi ;;
  
  
niederschaeffolsheim "de , soldat de la loi";;
	
type fraction = { nom: int; denom: int;};;
let simplifiable (tab: fraction array) : bool = (* O(n^2) si jamais on fait chaque fraction avec celle d'après... *)
	let is_same x1 x2 y1 y2 = x1*y2 = y1*x2 in (*\forall (x, x')\in\mathbb{Z}^2, (y, y') \in \mathbb{Z}^{*}\times\mathbb{Z}^{*}\\ \frac{x}{y} = \frac{x'}{y'} \Longleftrightarrow xy' = yx'*)
	let result = ref false in
	for i = 0 to (Array.length tab -1) do
		if not !result then
		begin		
		for y = (i+1) to (Array.length tab -1) do
			result := tab.(i).denom * tab.(y).denom <> 0 && is_same (tab.(i).nom) (tab.(y).nom) (tab.(i).denom) (tab.(y).denom) 
		done;
		end
	done;
	!result;;
	
	
	
	
let existesomme (tab: int array) : bool = let ret = ref false in
  for i = 0 to (Array.length tab - 1) do
    if(not !ret ) then
    for y = i+1 to (Array.length tab - 1) do
      if(not !ret ) then
      for x = y+1 to (Array.length tab - 1) do
        if tab.(i) = tab.(y) + tab.(x) then ret := true
      done;
    done;
  done;
  !ret ;;

let fincommune (str1: string) (str2: string) : int = 
  let counter = ref 0 in
  let min_len = min (String.length str1) (String.length str2) in
  for i = 0 to (min_len - 1) do
    if(str1.[i] = str2.[i] && i = !counter) then incr counter
  done;
  !counter;;
  
let decomp n = let get_next_prime n = let next = ref (n+1) in let is_prime num = if num mod 2 = 0 then num = 2 else begin let rec aux counter =  if num = counter then true else (num mod counter <> 0) && aux (counter+2) in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *) end in while not (is_prime !next) do   incr next; done; !next in  let rec aux liste copy prime =  if copy = 1 then liste else begin   if copy mod prime = 0 then match liste with   | (p, n)::q when p = prime -> aux ((p, n+1)::q) (copy/prime) prime (* MARCHE !*)   | _ -> aux ((prime, 1)::liste) (copy / prime) prime   else aux liste copy (get_next_prime prime) end in aux [] n 2;;

decomp 4829;; 
  
  
  
let kneckes (str: string) : string = 
  String.fold_left (fun acc car -> if car = ' ' then (acc^car^"hopla") else acc^car);;
  (*String.make ((String.length str) + (5*String.fold_left (fun acc car -> if car = ' ' then acc+1)))*)
  
  
  
  
  
  

  
  
  
  
  
  
  
  






(** Représentation d'un véhicule *)
type vehicule = {
  m : int; (** le numéro de série du véhicule *)
  p : int; (** le prix initial *)
  r : int; (** la taille du réservoir *)
  c : int; (** le coût au kilomètre *)
}

(**
   @param n le nombre de véhicules disponibles
   @param d la distance à parcourir
   @param v la liste des véhicules
*)
let rent n d v =
	let lst = Array.fold_left (fun acc el -> if el.r >= d then el::acc else acc) [] v in
	List.fold_left (fun acc el -> if (acc.p + acc.c*d) < (el.p + el.c*d) then acc else el) (List.nth lst) lst;;
  (** TODO Le numéro de modèle du véhicule revenant le moins cher ou $-1$ si
  aucun véhicule n'est disponible (la liste est vide ou aucun véhicule ne
  possède un réservoir suffisamment grand). Si deux modèles sont équivalents,
  le véhicule retenu sera celui-ci ayant été considéré en premier dans l'ordre
  de la liste. *)
  ()


let () =
  let n = read_int () in
  let d = read_int () in
  let v = List.init n (fun _ -> Scanf.sscanf (read_line ()) "%d %d %d %d" (fun m p r c -> {m; p; r; c})) in
  rent n d v
  
  

(**
   @param taille La taille de la liste de prénoms
   @param noms La liste de mots dont on doit extraire le préfixe
*)
let mcp taille noms =
	let bigger = Array.fold_left (fun acc el -> min acc (String.length el) 20001 noms in
  (** TODO Le préfixe commun au plus de mots de la liste passée en entrée *)
  ()

let () =
  let taille = read_int () in
  let noms = List.init taille (fun _ -> read_line ()) in
  mcp taille noms;;
  
  
  
let is_prime num = if num mod 2 = 0 then num = 2
  else begin
  let rec aux counter = 
  if num = counter then true
  else (num mod counter <> 0) && aux (counter+2)
  in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
  end;;
  
let stringify car = String.make 1 car;;
  
let kneckes (str: string) : string = 
  let new_str = ref "" in
  String.iteri (fun i el -> (if is_prime i && el = ' ' then new_str := !new_str ^ "hopla"); 
  										new_str := !new_str ^ (stringify el))
  !new_str;;

let pgcd fst scn = 
  let a = ref (max fst scn) in
  let b = ref (min fst scn) in
  let r = ref (!a mod !b) in
  while !r <> 0 do
    a := !b;
    b := !r;
    r := !a mod !b;
  done;
  !b;;  


pgcd 7 5;;




let is_prime num = if num mod 2 = 0 then num = 2
  else begin
    let rec aux counter = 
      if num = counter then true
      else (num mod counter <> 0) && aux (counter+2)
    in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
  end;;
  
let stringify car = String.make 1 car;;
  
let kneckes (str: string) : string = 
  let new_str = ref "" in
  String.iteri (fun i el -> (if is_prime i && el = ' ' then new_str := !new_str ^ " hopla"); 
                 new_str := !new_str ^ (stringify el)) str;
  !new_str;;

kneckes "Mais, vous savez, moi je ne crois pas qu’il y ait de bonne ou de mauvaise situation. Moi, si je devais résumer ma vie aujourd’hui avec vous, je dirais que c’est d’abord des rencontres, des gens qui m’ont tendu la main, peut-être à un moment où je ne pouvais pas, où j’étais seul chez moi. Et c’est assez curieux de se dire que les hasards, les rencontres forgent une destinée… Parce que quand on a le goût de la chose, quand on a le goût de la chose bien faite, le beau geste, parfois on ne trouve pas l’interlocuteur en face, je dirais, le miroir qui vous aide à avancer. Alors ce n’est pas mon cas, comme je le disais là, puisque moi au contraire, j’ai pu ; et je dis merci à la vie, je lui dis merci, je chante la vie, je danse la vie… Je ne suis qu’amour ! Et finalement, quand beaucoup de gens aujourd’hui me disent : « Mais comment fais-tu pour avoir cette humanité ? » Eh bien je leur réponds très simplement, je leur dis que c’est ce goût de l’amour, ce goût donc qui m’a poussé aujourd’hui à entreprendre une construction mécanique, mais demain, qui sait, peut-être simplement à me mettre au service de la communauté, à faire le don, le don de soi…";;


let is_prime num = if num mod 2 = 0 then num = 2
  else begin
    let rec aux counter = 
      if num = counter then true
      else (num mod counter <> 0) && aux (counter+2)
    in num <> 1 && aux 3; (* optimisable avec l'algo de Rabin - Miller... *)
  end;;
  
let stringify car = String.make 1 car;;


let kneckes (str: string) : string = 
  let compteur = ref 0 in
  let new_str = ref "" in
  String.iter (fun el -> 
      if el = ' ' then (
        incr compteur;
        if is_prime !compteur then new_str := !new_str ^ " hopla"
      );
      new_str := !new_str ^ (stringify el)
    ) str;
  
  !new_str;;



let sommeminmax (arr: int array) : int =
  Array.fast_sort (fun x y -> x - y) arr;
  let counter = ref 0 in
  for i = 0 to (Array.length arr - 1) do
  	if i mod 2 = 0 then counter := !counter + (max (arr.(i)) (arr.(i+1)));
  done;
  !counter;;

sommeminmax [|4;2;6;3;8;1|];;





(* Exercice 64 *)
type 'a lc = { mutable tete : 'a option; mutable suivant : 'a lc option };;
let creer_lc() = { tete = None; suivant = None };;
let rec taille_lc l =
  match l.tete, l.suivant with
  | None, _ -> 0
  | _, None -> 1
  | _, Some reste -> 1 + taille_lc reste;;

let rec inserer_lc l i x =
  match i, l.tete, l.suivant with
  | 0, None, _ -> l.tete <- Some x
  | 0, Some a, None -> let reste = { tete = Some a; suivant = None } in l.tete <- Some x; l.suivant <- Some reste
  | 0, Some a, Some reste -> let lbis = { tete = Some a; suivant = Some reste } in l.tete <- Some x; l.suivant <- Some lbis
  | _, None, _ -> failwith "Liste chaînée trop courte"
  | 1, _, None -> let reste = { tete = Some x; suivant = None } in l.suivant <- Some reste
  | _, _, None -> failwith "Liste chaînée trop courte"
  | _, _, Some reste -> inserer_lc reste (i-1) x;;


let miroirlc (lcv: 'a lc) = 
  let taille = taille_lc lcv in
  match taille with 
  | a when a < 1 -> creer_lc ()
  | size -> 
    let new_lc = creer_lc () in
    let next = ref lcv in
    for i = 0 to (size - 1) do
      inserer_lc new_lc i (!next.tete);
      next := (match !next.suivant with | Some s -> s | _ -> failwith "Suicide toi");
    done;
    new_lc;;

int_of_char;;


let fincommune (str1: string) (str2: string) : int = 
  let counter = ref 0 in
  let size1 = (String.length str1) in
  let size2 = (String.length str2) in
  let min_len = min size1 size2 in
  for i = 0 to (min_len - 1) do
    if(i = !counter && str1.[size1-i-1] = str2.[size2-i-1]) then incr counter
  done;
  !counter;;

fincommune "Bonjour" "jour";;

Array.map (fun x -> x * 2) [|1;2;3|];;


1 lsl 0;;


Array.to_list;;
List.filteri;;



