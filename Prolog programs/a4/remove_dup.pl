rmdup(L,L1):- rmAcc(L,[],L1).

rmAcc([],A,A).
rmAcc([H|T],A,L):- 
	isMember(A,H),
	rmAcc(T,A,L).
rmAcc([H|T],A,L):- rmAcc(T,[H|A],L).
