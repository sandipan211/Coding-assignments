exchange_first_last([],[]).
exchange_first_last([X],[X]).
exchange_first_last([X|L],L1):- ex(L,[X],L1,[]).

ex([X|L],A,L1,L2):- L=[],append(L2,A,L3),append([X],L3,L1).
ex([X|[Y|L]],A,L1,L2):- 
	append(L2,[X],L3),
	ex([Y|L],A,L1,L3).
