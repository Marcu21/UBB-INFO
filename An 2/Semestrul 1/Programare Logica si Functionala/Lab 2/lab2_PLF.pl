%inserare_crescator(L: lista, E: int, R: lista)
%model de flux: (i, i, o)
%L: lista in care se insereaza crescator elementul E, daca acesta nu este prezent deja
%E: elementul care se insereaza crescator in lista L, daca acesta nu este prezent deja
% R: lista rezultata in urma inserarii crescatoare a elementului E in
% lista L, in cazul in care acesta nu este prezent deja
inserare_crescator([], E, [E]).
inserare_crescator([H|T], E, R):- E < H, R = [E,H|T].
inserare_crescator([H|T], E, R):- E > H, inserare_crescator(T, E, R1), R = [H|R1].
inserare_crescator([H|T], E, R):- E = H, R = [H|T].

%sortare(L: lista, R: lista)
%model de flux: (i, o)
%L: lista care se sorteaza crescator fara pastrarea dublurilor
%R: lista rezultata in urma sortarii crescatoare fara pastrarea dublurilor
sortare([], []).
sortare([H|T], R):- sortare(T, R1), inserare_crescator(R1, H, R).

%lista_eterogena(L: lista, R: lista)
%model de flux: (i, o)
%L: lista eterogena ale carei subliste se sorteaza crescator fara pastrarea dublurilor
%R: lista eterogena rezultata in urma sortarii crescatoare ale listei L fara pastrarea dublurilor
lista_eterogena([], []).
lista_eterogena([H|T], R):- is_list(H), sortare(H, R1), lista_eterogena(T, R2), R = [R1|R2],!.
lista_eterogena([H|T], R):- lista_eterogena(T, R1), R = [H|R1].
