isMember([X|_],X).
isMember([_|Rest],X):-
	isMember(Rest,X).
