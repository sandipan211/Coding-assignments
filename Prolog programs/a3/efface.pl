efface(_,[],[]).
efface(X,[X|L],L):-!.
efface(A,[B|L],[B|M]):- efface(A,L,M).
