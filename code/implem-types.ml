type unknown = { id : int }

type 'a var_type =
  | Unknown of unknown
  | Instanciated of 'a

and qual =
  | Kernel
  | User
  | QVar of qual var_type ref

and simple =
  | Int
  | Float
  | Fun of simple list * simple list
  | Ptr of qual * simple
  | Array of simple
  | Struct of (int * simple) list ref
  | Var of simple var_type ref
