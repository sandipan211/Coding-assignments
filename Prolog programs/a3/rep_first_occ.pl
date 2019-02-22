rfo(_,_,[],[]).
rfo(X,Y,[X|L1],[Y|L1]):-!.
rfo(X,Y,[Z|L1],[Z|L2]):- rfo(X,Y,L1,L2).
