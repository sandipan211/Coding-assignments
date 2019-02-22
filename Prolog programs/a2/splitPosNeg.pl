splitPosNeg([],[],[]).
splitPosNeg([X|Rest],[X|LP],LN):-
    X>=0,
    splitPosNeg(Rest,LP,LN).
splitPosNeg([Y|Rest],LP,[Y|LN]):-
    Y<0,
    splitPosNeg(Rest, LP, LN).