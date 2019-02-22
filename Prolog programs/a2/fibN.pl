fibN(0,[]).
fibN(1,[0]).
fibN(2,[0,1]).
fibN(N,L):-
	N1 is N-1,
	fibN(N1,L1),
	append(T1,[X|[Y]],L1),
	addint(X,Y,T2),
	append(L1,[T2],L).
