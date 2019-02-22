rev(L,M):- rev_acc(L,[],M).

rev_acc([],A,A).
rev_acc([X|L],A,M):-
	rev_acc(L,[X|A],M).
	
