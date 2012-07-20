Decl
  ( "x"
  , Newspeak.Scalar (Newspeak.Int (Newspeak.Signed, 32))
  , ()
  , [ Decl
        ( "p"
        , Newspeak.Scalar Newspeak.Ptr
        , ()
        , [ Set
              ( Local "p"
              , ( AddrOf (Local "x")
                , ()
                )
              , Newspeak.Scalar Newspeak.Ptr
              )
          ; Set
              ( Local "x"
              , ( Const (CInt Nat.zero)
                , ()
                )
              , Newspeak.Scalar (Newspeak.Int (Newspeak.Signed, 32))
              )
          ]
        )
    ]
  )
