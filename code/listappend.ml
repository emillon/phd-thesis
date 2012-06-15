let rec append lx ly =
  match lx with
    |  []   -> ly
    | x::xs -> x::append lx ly
