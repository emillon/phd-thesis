let rec infer_stmtkind env sk =
  match sk with
  (* [...] *)
  | T.Decl (n, nty, _ty, blk) ->
      let var = T.Local n in
      let t0 = new_unknown () in
      let new_env = Env.add (VLocal n) (Some nty) t0 env in
      let blk' = infer_blk new_env blk in
      let ty = lval_type new_env var in
      T.Decl (n, nty, ty, blk')
  (* [...] *)
  | T.Call (args, fexp, rets) ->
      let infer_arg (e, nt) =
        let et = infer_exp env e in
        (et, nt)
      in

      let infer_ret (lv, nt) =
        (infer_lv env lv, nt)
      in

      let args' = List.map infer_arg args in
      let rets' = List.map infer_ret rets in

      let t_args = List.map (fun ((_, t), _) -> t) args' in
      let t_rets = List.map (fun (lv, _) -> lval_type env lv) rets' in

      let (fexp', tf) = infer_funexp env fexp in
      let call_type = Fun (t_args, t_rets) in
      unify tf call_type;
      T.Call (args', fexp', rets')
