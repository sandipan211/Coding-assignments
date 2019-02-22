sqroot(N,X):- sqroot_acc(N,1,X).

sqroot_acc(N,I,X):- multint(I,I,N),  X is I.
sqroot_acc(N,I,X):-
	I1 is I+1,
	multint(I,I,N1),
	N1 < N,
	sqroot_acc(N,I1,X).
		
