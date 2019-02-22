fact2(N,Res):- N=0, Res is 1, !.
fact2(N,Res):- fact_acc(N,1,Res).

fact_acc(N,I,R):- I=N, multint(I,1,R).
fact_acc(N,I,R):-
	I1 is I+1,
	fact_acc(N,I1,R1),
	multint(I,R1,R).
