trim(0,L,L1):- append([],L,L1).
trim(N,[X|L],L1):-
	N1 is N-1,
	trim(N1,L,L1).
