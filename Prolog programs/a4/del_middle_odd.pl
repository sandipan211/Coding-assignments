dmo(L,L1):- 
	lena4(L,Res),
	Index is (Res-1)/2,
	dmo1(L,[],Index,L1).

dmo1([X|L],A,0,L1):- append(A,L,L1).
dmo1([X|L],A,N,L1):-
	append(A,[X],L2),
	N1 is N-1,
	N1>=0,
	dmo1(L,L2,N1,L1).
