deleteAll(_,[],[]).
deleteAll(A,[A|L],M):-!,deleteAll(A,L,M).
deleteAll(A,[B|L],[B|M]):-
    deleteAll(A,L,M).
