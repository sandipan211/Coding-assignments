dme(L,L1):-
        lena4(L,Res),
        Index is Res/2-1,
        dme1(L,[],Index,L1).

dme1([X|[Y|L]],A,0,L1):- append(A,L,L1).
dme1([X|L],A,N,L1):-
        append(A,[X],L2),
        N1 is N-1,
        N1>=0,
        dme1(L,L2,N1,L1).

