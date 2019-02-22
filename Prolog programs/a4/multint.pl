
multint(_,0,0).
multint(0,_,0).
multint(1,X,X).
multint(X,1,X).
multint(X,Y,Res):-
    ((X>0,Y>0);(X<0,Y>0)),
    Y1 is Y-1,
    multint(X,Y1,Res1),
    Res is Res1+X.
multint(X,Y,Res):-
    X>0,Y<0,
    X1 is X-1,
    multint(X1,Y,Res1),
    Res is Res1+Y.
multint(X,Y,Res):-
    X<0,Y<0,
    X1 is X+1,
    multint(X1,Y,Res1),
    Z is Y-Res1,
    subint(0,Z,Res).
