lena4(L,Res):- len_acc(L,0,Res).

len_acc([],A,A).
len_acc([X|L],A,R):- A1 is A+1, len_acc(L,A1,R).
