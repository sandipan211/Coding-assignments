substitute(_,_,[],[]).
substitute(S,T,[S|L],[T|M]):- !,substitute(S,T,L,M).
substitute(S,T,[A|L],[A|M]):-
	substitute(S,T,L,M).
