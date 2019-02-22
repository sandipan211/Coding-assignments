length1([],0).
length1([X|Rest],s(N)):-
	length1(Rest,N).
