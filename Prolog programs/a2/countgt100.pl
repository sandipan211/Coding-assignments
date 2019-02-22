countgt100([],0).
countgt100([X|Rest],N):-
    X>100.0,
    countgt100(Rest, N1),
    N is N1+1.
countgt100([X|Rest],N):-
    X=<100.0,
    countgt100(Rest,N).