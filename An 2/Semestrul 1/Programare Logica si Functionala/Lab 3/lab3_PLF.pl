%adaug(E: int, L: lista, R: lista)
%model de flux: (i, i, o)
%E: elementul care se adauga la finalul listei L
%L: lista in care se adauga la final elementul E
%R: lista rezultata in urma adaugarii la final a elementului E in lista L
adaug([], E, E).
adaug([H|T], E, R):- adaug(T, E, R1), R=[H|R1].
%membru(E: int, L: lista)
%model de flux: (i, i)
%E: elementul a carui presenta se verifica in lista L
%L: lista in care se verifica prezenta elementului E
membru(E, [H|_]):- E = H.
membru(E, [H|T]):- E \= H, membru(E, T).
%ultim(L: lista, E: int)
%L: lista in care se verifica daca ultimul element este egal cu E
%E: elementul cu care se verifica daca este egal ultimul element al listei L
ultim([H], E):- H = E.
ultim([_|T], E):- ultim(T, E).
%candidat(E1: int, E2: int)
%model de flux: (i, o)
%E1: ultimul element al listei
%E2: elementul nou care va fi inserat in lista pe ultima pozitie
candidat(LastElement, NextElement) :-
    (NextElement is LastElement + 1; NextElement is LastElement - 1),
    membru(NextElement, [0, -1, 1]).
candidat(LastElement, NextElement) :-
    (NextElement is LastElement + 2; NextElement is LastElement - 2),
    membru(NextElement, [0, -1, 1]).
%generare(LungimeFinala: int, LungimeCurenta: int, Lista: list, R: list)
%model de flux: (i, i, i, o)
% LungimeFinala: lungimea la care trebuie sa ajunga lista care se
% genereaza
% LungimeCurenta: lungimea actuala a listei care se genereaza
% Lista: lista generata pana acum
% R: lista finala care indeplineste conditiile
generare(Lungime, Lungime, Subsir, Subsir) :-
    ultim(Subsir, 0).
generare(Lungime, LungimeCurenta, Subsir, Rezultat) :-
    LungimeCurenta < Lungime,
    ultim(Subsir, LastElement),
    candidat(LastElement, NewElement),
    NextLungime is LungimeCurenta + 1,
    adaug(Subsir, [NewElement], NewSubsir),
    generare(Lungime, NextLungime, NewSubsir, Rezultat).
%apel(N: int, R: lista)
%N: numarul in baza caruia se calculeaza lungimea
%R: lista rezultata in urma generarii
apel(N, Rezultat) :-
    Lungime is 2 * N + 1,
    generare(Lungime, 1, [0], Rezultat).







