reo([X],[X]).
reo(_,[]).
reo([X|[Y|L]],[X|L1]):- reo(L,L1).
