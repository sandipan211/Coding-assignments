cls([],[]).
cls([X|L],L1):- cls1(L,[X],L1,[]).

cls1([],A,L1,L2):- append(L2,A,L1).
cls1([X|L],A,L1,L2):-
	append(L2,[X],L3),
	cls1(L,A,L1,L3).
