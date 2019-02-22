
trimlast(N,L,L1):-
        rev(L,M),
        trim(N,M,L2),
	rev(L2,L1).


