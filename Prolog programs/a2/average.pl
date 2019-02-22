avg(L,Avg):-
	sum(L, Sum),
	leng(L,Len), 
	Len>0,
	Avg is Sum/Len.
