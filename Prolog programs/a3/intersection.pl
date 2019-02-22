intersection([],L,[]).
intersection([X|L1],L2,[X|L3]):- isMember(L2,X), !, intersection(L1,L2,L3).
intersection([X|L1],L2,L3):- intersection(L1,L2,L3).
