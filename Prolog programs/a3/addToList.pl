addToList(A,[],[A]).
addToList(A,L,L):-isMember(L,A),!.
addToList(A,L,[A|L]).
