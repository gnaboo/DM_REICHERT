(* Exercice 61 *) (* COMPILE *)
let existesomme (tab: int array) : bool = 
  let ret = ref false in
  for i = 0 to (Array.length tab - 1) do
    if(not !ret ) then
    for y = 0 to (Array.length tab - 1) do
      if(not !ret && i <> y) then
      for x = 0 to (Array.length tab - 1) do
        if y <> x && tab.(i) = tab.(y) + tab.(x) then ret := true
      done;
    done;
  done;
  !ret;;


(* Exercice 62 *) (* COMPILE *)
let fincommune (str1: string) (str2: string) : int = 
  let counter = ref 0 in
  let size1 = (String.length str1) in
  let size2 = (String.length str2) in
  let min_len = min size1 size2 in
  for i = 0 to (min_len - 1) do
    if(i = !counter && str1.[size1-i-1] = str2.[size2-i-1]) then incr counter
  done;
  !counter;;

  



(* Exercice 66 *)
let build_frequency_table arr =
  let table = Hashtbl.create (Array.length arr) in
  Array.iter (fun x ->
    let count = Hashtbl.find_opt table x |> Option.value ~default:0 in
    Hashtbl.replace table x (count + 1)
  ) arr;
  table
;;

let max_frequency table =
  Hashtbl.fold (fun _ count acc -> max acc count) table 0
;;

let values_with_max_freq table max_freq =
  Hashtbl.fold (fun key count acc -> if count = max_freq then key :: acc else acc) table []
;;

let indices_of_value arr value =
  let indices = Array.fold_left (fun (idxs, i) x -> 
    if x = value then (i :: idxs, i + 1) else (idxs, i + 1)
  ) ([], 0) arr in
  List.rev (fst indices)
;;

let median_of_sorted_list lst =
  let len = List.length lst in
  if len = 0 then None
  else if len mod 2 = 1 then Some (List.nth lst (len / 2))
  else Some (List.nth lst ((len / 2) - 1))
;;

let medianefreq arr =
  let size = Array.length arr in
  if size < 3 then 0 else
  let table = build_frequency_table arr in
  let max_freq = max_frequency table in
  let values = values_with_max_freq table max_freq in

  let indexed_values = 
    List.map (fun v ->
      let indices = indices_of_value arr v in
      let sum_indices = List.fold_left ( + ) 0 indices in
      let median_index = median_of_sorted_list indices |> Option.get in
      (sum_indices, median_index, v)
    ) values
  in

  let _, min_median, _ = List.fold_left (fun (max_sum, min_med, best_value) (sum, median, value) ->
    if sum > max_sum then (sum, median, value)
    else if sum = max_sum && median < min_med then (sum, median, value)
    else (max_sum, min_med, best_value)
  ) (0, size, 0) indexed_values in

  min_median
;;