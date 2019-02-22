leng([],0).
leng([X|Rest],Len):-
	leng(Rest, LenRest),
	Len is LenRest+1.
