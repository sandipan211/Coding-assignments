setdiff([],L,[]).
setdiff([X|L1],L2,L3):- isMember(L2,X), !, setdiff(L1,L2,L3).
setdiff([X|L1],L2,[X|L3]):- setdiff(L1,L2,L3).
