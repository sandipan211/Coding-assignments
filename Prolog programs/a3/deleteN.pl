
deleteN(1,[X],[]):-!.
deleteN(1,[X|[Y|L]],[Y|L]):-!.
deleteN(N,[A|L],[A|L1]):-
	N1 is N-1,
	deleteN(N1,L,L1).
