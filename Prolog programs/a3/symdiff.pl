symdiff(A,B,L):- union(A,B,L1), intersection(A,B,L2), setdiff(L1,L2,L).
