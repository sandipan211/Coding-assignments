last1([X],X).
last1([_|Rest],X):-
	last1(Rest,X).
