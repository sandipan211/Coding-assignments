facto(0,1).
facto(Num,Res):-
    X is Num-1,
    facto(X,Res1),
    multint(Num,Res1,Res).

