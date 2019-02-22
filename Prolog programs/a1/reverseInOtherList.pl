reverse1([],[]).
reverse1([H|T],L):-
	reverse1(T,X),
	append(X,[H],L).
