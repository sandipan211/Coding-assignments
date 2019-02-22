union([],L,L).
union([X|L1],L2,L3):- isMember(L2,X), !, union(L1,L2,L3).
union([X|L1],L2,[X|L3]):- union(L1,L2,L3).
