let unify_structs rfa rfb =
  let fa = !rfa in
  let fb = !rfb in

  let new_a = ref [] in
  let new_b = ref [] in

  let unify_fields = function
    | _, InBoth (ta, tb) -> unify_now ta tb
    | k, OnlyL f -> new_b := (k,f) :: !new_b
    | k, OnlyR f -> new_a := (k,f) :: !new_a
  in

  List.iter unify_fields (compare_lists fa fb);
  let by_offset (x, _) (y, _) =
    compare x y
  in
  rfa := List.sort by_offset (!new_a @ !rfa);
  rfb := List.sort by_offset (!new_b @ !rfb)
