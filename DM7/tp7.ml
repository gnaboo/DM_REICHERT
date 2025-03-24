(* Exercice 1 en C *)

(* Exercice 2 *)

type 'a tr = { mutable taille : int; mutable donnees : 'a array };;

let creer_tr capacite initial = assert (capacite >= 0);
{ taille = 0 ; donnees = Array.make capacite initial };;

let taille_tr t = t.taille;;

let acces_tr t i =
  assert (i >= 0 && i < t.taille);
  t.donnees.(i);;

let modif_tr t i x =
  assert (i >= 0 && i < t.taille);
  t.donnees.(i) <- x;;

let redimensionne_tr t =
  let nv_taille = 2 * t.taille in
  let nv_tab = Array.make nv_taille t.donnees.(0) in
  for i = 1 to t.taille - 1 do nv_tab.(i) <- t.donnees.(i) done;
  t.donnees <- nv_tab;;

let append_tr t x =
  if t.taille = Array.length t.donnees then redimensionne_tr t;
  t.donnees.(t.taille) <- x;
  t.taille <- t.taille + 1;;

let pop_tr t =
  assert (t.taille > 0);
  let rep = t.donnees.(t.taille - 1) in t.taille <- t.taille - 1; rep;;

(* Exercice 3 en C *)

(* Exercice 4 en C *)

(* Exercice 5 *)

(* En pratique, une autre idée aurait été que la tête ne soit pas mutable et que None soit réservé au fond. *)
type 'a lc = { mutable tete : 'a option; mutable suivant : 'a lc option };;

let creer_lc() = { tete = None; suivant = None };;

let tete_lc l = (* Résidu d'une consigne étendue retirée entre temps. *)
  match l.tete with
  | None -> failwith "Liste chaînée vide"
  | Some a -> a;;

let modif_tete_lc l x = (* Idem *)
  match l.tete with
  | None -> failwith "Liste chaînée vide"
  | Some a -> l.tete <- Some x;;

let queue_lc l = (* Idem *)
  match l.tete, l.suivant with
  | None, _ -> failwith "Liste chaînée vide"
  | _, None -> creer_lc ()
  | _, Some reste -> reste;;

let rec taille_lc l =
  match l.tete, l.suivant with
  | None, _ -> 0
  | _, None -> 1
  | _, Some reste -> 1 + taille_lc reste;;

let rec acces_lc l i =
  match i, l.tete, l.suivant with
  | _, None, _ -> failwith "Liste chaînée vide"
  | 0, Some a, _ -> a
  | _, _, None -> failwith "Liste chaînée trop courte"
  | _, _, Some reste -> acces_lc reste (i-1);;

let rec inserer_lc l i x =
  match i, l.tete, l.suivant with
  | 0, None, _ -> l.tete <- Some x
  | 0, Some a, None -> let reste = { tete = Some a; suivant = None } in l.tete <- Some x; l.suivant <- Some reste
  | 0, Some a, Some reste -> let lbis = { tete = Some a; suivant = Some reste } in l.tete <- Some x; l.suivant <- Some lbis
  | _, None, _ -> failwith "Liste chaînée trop courte"
  | 1, _, None -> let reste = { tete = Some x; suivant = None } in l.suivant <- Some reste
  | _, _, None -> failwith "Liste chaînée trop courte"
  | _, _, Some reste -> inserer_lc reste (i-1) x;;

let rec retirer_lc l i =
  match i, l.tete, l.suivant with
  | _, None, _ -> failwith "Liste chaînée vide"
  | 0, _, None -> l.tete <- None
  | 0, _, Some { tete = a; suivant = b } -> l.tete <- a; l.suivant <- b
  | _, _, None -> failwith "Liste chaînée trop courte"
  | _, _, Some reste -> retirer_lc reste (i-1);;

(* Exercice 6 *)

let creer_lcp () = [];;

let taille_lcp l = List.length l;;

let rec acces_lcp l i = match i, l with
| _, [] -> failwith "Liste chaînée trop courte"
| 0, a::_ -> a
| _, _::q -> acces_lcp q (i-1);;

let rec inserer_lcp l i x = match i, l with
| 0, l -> x::l
| _, [] -> failwith "Liste chaînée trop courte"
| _, a::q -> a::(inserer_lcp q (i-1) x);;

let rec retirer_lcp l i = match i, l with
| _, [] -> failwith "Liste chaînée trop courte"
| 0, a::q -> q
| _, a::q -> a::(retirer_lcp q (i-1));;

(* Exercice 7 en C *)

(* Exercice 8 en C *)

(* Exercice 9 *)

type 'a fileb = { mutable taille : int; mutable tete : int; mutable queue : int; donnees : 'a array };;

let creer_fileb capacite initial = { taille = 0; tete = 0; queue = -1; donnees = Array.make capacite initial };;

let enfiler_fileb f x =
  let n = Array.length f.donnees in
  assert (f.taille < n);
  f.taille <- f.taille + 1;
  f.queue <- (f.queue + 1) mod n;
  f.donnees.(f.queue) <- x;;

let defiler_fileb f =
  let n = Array.length f.donnees in
  assert (f.taille > 0);
  let rep = f.donnees.(f.tete) in
  f.taille <- f.taille - 1;
  f.tete <- (f.tete + 1) mod n;
  rep;;

let est_vide_fileb f = f.taille = 0;;

(* Exercice 10 *)

let creer_file () = [], [];;

let enfiler_file (pe, ps) x = (x::pe, ps);;

let transfert (pe, ps) =
  assert (ps = []);
  ([], List.rev pe);; (* Ou l'écrire avec des opérations de pile… *)

let defiler_file (pe, ps) =
  let (pe1, pe2) = if ps = [] then transfert (pe, ps) else (pe, ps) in
  match pe2 with
  | [] -> failwith "File vide"
  | a::q -> a, (pe1, q);;

let est_vide_file (pe, ps) = pe = [] && ps = [];;



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
  | a when a < 1 -> creer_lc
  | a when a = 1 -> lcv
  | size -> 
    let new_lc = creer_lc in
    for i = 0 to (size - 1) do
      inserer_lc l i !next;
      next := !next.suivant;
    done;
    new_lc;;