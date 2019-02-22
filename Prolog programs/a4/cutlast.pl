cutlast([],[]).
cutlast([_],[]). 
cutlast([X|L],L1):- cutlast(L,L2),append([X],L2,L1).
