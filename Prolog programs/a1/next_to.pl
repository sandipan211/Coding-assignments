next_to([X|[Y|_]],X,Y).
next_to([Y|[X|_]],X,Y).
next_to([_|Rest],X,Y):-
	next_to(Rest,X,Y).
