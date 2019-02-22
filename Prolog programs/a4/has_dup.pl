
has_dup([H|T]):- isMember(T,H),!.
has_dup([H|T]):-has_dup(T).
