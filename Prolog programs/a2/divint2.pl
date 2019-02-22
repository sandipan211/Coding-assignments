divint(X,Y,Res):- X>=0,Y>0, divint1(X,Y,Res).

divint(X,Y,Res):- X<0,Y>0, 
		  subint(0,X,X1),
	          divint1(X1,Y,Res2),
		  subint(0,Res2,Res).

divint(X,Y,Res):- X>=0,Y<0,
                  subint(0,Y,Y1),
                  divint1(X,Y1,Res2),     
                  subint(0,Res2,Res).

divint(X,Y,Res):- X<0,Y<0, 
                  subint(0,X,X1),
		  subint(0,Y,Y1),
                  divint1(X1,Y1,Res).  
                 


divint1(X,1,X).
divint1(X,Y,Res):- X<Y, Res is 0.
divint1(X,Y,Res):-   
    X1 is X-Y,
    divint1(X1,Y,Res1),
    Res is Res1+1.
