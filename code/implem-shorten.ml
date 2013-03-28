let rec shorten = function
  | Var ({contents = Instanciated (Var _ as t)} as vt) ->
      let t2 = shorten t in
      vt := Instanciated t;
      t2
  | Var {contents = Instanciated t} -> t
  | t -> t
