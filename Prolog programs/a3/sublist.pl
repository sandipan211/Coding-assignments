sublist([],_).
sublist([X|L],[X|M]):- prefix(L,M),!.
sublist([X|L],[Y|M]):- sublist([X|L],M).

prefix([],_).
prefix([X|L],[X|M]):- prefix(L,M).
