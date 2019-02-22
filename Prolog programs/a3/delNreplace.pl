
deleteN(1,Y,[X|L],[Y|L]):-!.
deleteN(N,Y,[A|L],[A|L1]):-
        N1 is N-1,
        deleteN(N1,Y,L,L1).

