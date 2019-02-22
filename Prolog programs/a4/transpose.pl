transpose([],[],[]).
transpose([X|L1],[Y|L2],L):-
	transpose(L1,L2,L3),
	append([[X,Y]],L3,L).
