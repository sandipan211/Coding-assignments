addint(X,0,X).
addint(0,X,X).
addint(X,Y,Res):-
    X>0,Y>0,
    Y1 is Y-1,
    addint(X,Y1,Res1),
    Res is Res1+1.
addint(X,Y,Res):-
    X>0,Y<0,
    Y1 is Y+1,
    addint(X,Y1,Res1),
    Res is Res1-1.
addint(X,Y,Res):-
    X<0,Y>0,
    X1 is X+1,
    addint(X1,Y,Res1),
    Res is Res1-1.
addint(X,Y,Res):-
    X<0,Y<0,
    Y1 is Y+1,
    addint(X,Y1,Res1),
    Res is Res1-1.
