reo2([],[]).
reo2([X|L],[X|L1]):- subseq(L,L1).

subseq(_,[]).
subseq([X|L],[X|L1]):- subseq(L,L1).
subseq([X|L],[Y|L1]):- subseq(L,[Y|L1]).
