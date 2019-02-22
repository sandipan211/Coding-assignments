interleave(L1,L2,L):- il1(L1,L2,[],L).
	
il1([],M,A,L):- append(A,M,L).
il1(M,[],A,L):- append(A,M,L).

il1([X|L1],[Y|L2],A,L):-
	append(A,[X],P),
	append(P,[Y],Q),
	il1(L1,L2,Q,L).
