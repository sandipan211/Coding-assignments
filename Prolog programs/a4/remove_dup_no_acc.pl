rmdup2([],[]).
rmdup2([X|L],L1):- rmele(X,L,L2),
		   rmdup2(L2,L3),
                   L1 = [X|L3].
		   

rmele(_,[],[]).
rmele(X,[X|L],M):-rmele(X,L,M).
rmele(X,[Y|L],M):-rmele(X,L,P),
		  M = [Y|P]. 
