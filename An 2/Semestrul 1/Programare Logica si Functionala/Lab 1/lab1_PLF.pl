%nr_ap(L:lista, E: int, R: int)
%model flux: (i, i, o)
%L: lista in care numaram aparitiile lui E
%E: elementul ale carui aparitii le numaram
%R: numarul de aparitii ale lui E in L
nr_ap([], _, 0).
nr_ap([A|L], E, R):- A=E, nr_ap(L, E, R1), R is R1+1.
nr_ap([A|L], E, R):- A\=E, nr_ap(L, E, R).

%e_multime(L: lista)
%model flux: (i)
%L: lista pe care o verificam daca e multime
e_multime([]).
e_multime([A|L]):- nr_ap(L, A, R), R=0, e_multime(L).

%elim_nr(L: lista, E: int, R: lista, N: int)
%model flux: (i, i, o, i)
%L: lista din care se elimina primele 3 aparitii ale lui E
%E: elementul ale carui primele 3 aparitii se sterg din lista L
%R: lista rezultata in urma stergerii primelor 3 aparitii ale lui E in L
%N: numarul primelor aparitii ale lui E care vor fi sterse din L
elim_nr([], _, [], _).
elim_nr([A|L], E, R, N):- A=E, N>0, N1 is N-1, !, elim_nr(L, E, R, N1).
elim_nr([A|L], E, R, N):- elim_nr(L, E, R1, N), R=[A|R1].

% elim_primele_3(L: lista, E: int, R: lista)
% model flux: (i, i, o)
% L: lista din care se elimina primele 3 aparitii ale lui E
% E: elementul ale carui primele 3 aparitii se sterg din lista L
% R: lista rezultata in urma stergerii primelor 3 aparitii ale lui E in L
elim_primele_3(L, E, R) :- elim_nr(L, E, R, 3).
