generateNum(X,X,[X]).
generateNum(N1,N2,[N1|L]):-
    N3 is N1+1,
    generateNum(N3,N2,L).