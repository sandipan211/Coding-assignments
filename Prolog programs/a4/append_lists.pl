append([],L,L).
append([X|Rest1],List2,[X|List3]):-
	append(Rest1, List2, List3).
