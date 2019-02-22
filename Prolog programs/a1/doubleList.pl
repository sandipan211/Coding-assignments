double([],[]).
double([X],[X,X]).
double([X|Rest],[X,X|L]):-
	double(Rest, L).
