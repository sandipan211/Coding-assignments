subset([],_).
subset([A|L1],L2):- isMember(L2,A),
		    subset(L1,L2).

