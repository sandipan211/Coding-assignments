max(X,Y,X):- X>=Y.
max(X,Y,Y):- X<Y.

listMax([X],X).
listMax([X|Rest], Max):-
	listMax(Rest, MaxRest),
	max(X,MaxRest,Max).
