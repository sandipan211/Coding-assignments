inner_product([],[],0).

inner_product([A|L1],[B|L2],X):- 
	multint(A,B,Res),
	inner_product(L1,L2,Res1),
	X is Res + Res1.
