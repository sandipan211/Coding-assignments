flatten([], []).
flatten([L|Rest], L1) :-
    flatten(L, L2),
    flatten(Rest, L3),
    append(L2,L3,L1).

flatten(L,[L]).
