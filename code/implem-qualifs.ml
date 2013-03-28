let rec shorten_q = function
  | QVar ({contents = Instanciated (QVar _ as t)} as vt) ->
      let t2 = shorten_q t in
      vt := Instanciated t;
      t2
  | QVar {contents = Instanciated t} -> t
  | t -> t

let rec unify_quals a b =
  let sa = shorten_q a in
  let sb = shorten_q b in
  match (sa, sb) with
  | User, User -> ()
  | Kernel, Kernel -> ()
  | ((QVar ({contents = Unknown na} as ra)),
     (QVar  {contents = Unknown nb})) ->
       begin
         if na <> nb then
           ra := Instanciated sb
       end
  | ((QVar ({contents = Unknown {id = n}} as r)), q)
    ->
      begin
        if occurs_q n q then
          occurs_q_check_failed sa sb
        else
          r := Instanciated q
      end
  | (_, (QVar ({contents = Unknown _}))) -> unify_quals sb sa
  | _ -> Utils.error "Cannot unify qualifiers:\n  %s\n  %s\n"
                        (string_of_qual sa)
                        (string_of_qual sb)
