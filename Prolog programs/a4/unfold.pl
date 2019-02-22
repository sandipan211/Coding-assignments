unfold(L,L1):- 
        lena4(L,Res),
        Index is (Res-1)/2,
   	unfold1(L,[],Index,L1).


unfold1([X|L],A,N,L1):-
	append(A,[X],L2),
	N1 is N-1,
	N1 >= 0,
	unfold1(L,L2,N1,L1).


unfold1([X|L],A,0,L1):- 
	rev(A,L2),
	append(L2,[X],L3),
	rev(L,L4),
	append(L3,L4,L1).
