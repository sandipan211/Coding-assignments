samelen([],[]).
samelen([X|Rest1],[Y|Rest2]):-
        samelen(Rest1, Rest2).

