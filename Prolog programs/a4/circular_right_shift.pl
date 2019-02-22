crs([],[]).
crs(L,L1):- crs1(L,[],L1).

crs1([X|L],L1,L2):-
	L \= [],
	!,
        append(L1,[X],L3),
        crs1(L,L3,L2).

crs1([X|_],L1,L2):- append([X],L1,L2).
