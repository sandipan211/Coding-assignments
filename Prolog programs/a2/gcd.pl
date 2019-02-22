gcd(0,X,X):- X>0, !.
gcd(X,Y,Z):- X >= Y, X1 is X-Y, gcd(X1, Y, Z).
gcd(X,Y,Z):- X < Y, X1 is Y-X, gcd(X1, X, Z).
