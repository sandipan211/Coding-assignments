subint(X,0,X).
subint(X,Y,Res):-
    X>=0,Y>0,
    Y1 is Y-1,
    subint(X,Y1,Res1),
    Res is Res1-1.
subint(X,Y,Res):-
    X>=0,Y<0,
    Y1 is Y+1,
    subint(X,Y1,Res1),
    Res is Res1+1.
subint(X,Y,Res):-
    X<0,Y>0,
    Y1 is Y-1,
    subint(X,Y1,Res1),
    Res is Res1-1.
subint(X,Y,Res):-
    X<0,Y<0,
    Y1 is Y+1,
    subint(X,Y1,Res1),
    Res is Res1+1.