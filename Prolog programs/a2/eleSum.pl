sum([],0).
sum([X|Rest],Sum):-
	sum(Rest, SumRest),
	Sum is SumRest +X.
