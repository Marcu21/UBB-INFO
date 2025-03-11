#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "service.h"

void run_domain_tests()
{
    MateriePrima* materie_prima = creeaza_materie_prima("materie", "prod", 5);
    assert(strcmp(materie_prima->nume, "materie") == 0);
    assert(strcmp(materie_prima->producator, "prod") == 0);
    assert(materie_prima->cantitate == 5);
    assert(validare(*materie_prima) == 1);

    distruge_materie_prima(materie_prima);

    materie_prima = creeaza_materie_prima("materie", "prod", -1);
    assert(validare(*materie_prima) == 0);
    distruge_materie_prima(materie_prima);
    materie_prima = creeaza_materie_prima("", "prod", 2);
    assert(validare(*materie_prima) == 0);
    MateriePrima* materie_prima2 = copy_materie(materie_prima);
    assert(strcmp(materie_prima2->nume, materie_prima->nume) == 0);
    assert(strcmp(materie_prima2->producator, materie_prima->producator) == 0);
    assert(materie_prima2->cantitate == materie_prima->cantitate);
    distruge_materie_prima(materie_prima);
    distruge_materie_prima(materie_prima2);
    printf("domain passed\n");
}

void run_repo_tests()
{
    MateriiPrime* materii_prime;
    materii_prime = creeaza_vid();
    MateriePrima* materie_prima = creeaza_materie_prima("m1", "p1", 2);
    adauga_materie_prima(materii_prime, materie_prima);
    assert(materii_prime->used == 1);
    MateriePrima* materie_prima2 = creeaza_materie_prima("m2", "p2", 2);
    adauga_materie_prima(materii_prime, materie_prima2);
    assert(materii_prime->used == 2);
    MateriePrima* materie_prima3 = creeaza_materie_prima("m3", "p3", 99);
    MateriiPrime* materii_prime2;
    materii_prime2 = copy_list(materii_prime);
    assert(materii_prime2->used == 2);
    modifica_materie_prima(materii_prime, 1, *materie_prima3);
    assert(((MateriePrima*)materii_prime->array[1])->cantitate == 99);
    sterge_materie_prima(materii_prime, 0);
    assert(materii_prime->used == 1);
    sterge_materie_prima(materii_prime, 0);
    assert(materii_prime->used == 0);
    //free(materie_prima);
    //free(materie_prima2);

    distruge_materie_prima(materie_prima3);
    distruge_materii_prime(materii_prime, (DestroyFunction)distruge_materie_prima);
    distruge_materii_prime(materii_prime2, (DestroyFunction)distruge_materie_prima);
    printf("repo passed\n");
}

void run_service_tests()
{
    MateriiPrime* materii_prime;
    materii_prime = creeaza_vid();
    MateriePrima* materie_prima = creeaza_materie_prima("m1", "p1", 2);
    adauga_element(materii_prime, materie_prima);
    assert(materii_prime->used == 1);
    MateriePrima* materie_prima2 = creeaza_materie_prima("m2", "p2", 2);
    adauga_element(materii_prime, materie_prima2);
    assert(materii_prime->used == 2);
    MateriePrima* materie_prima3 = creeaza_materie_prima("m3", "p3", -2);
    assert(adauga_element(materii_prime, materie_prima3) == 0);
    MateriePrima* materie_prima4 = creeaza_materie_prima("m3", "p3", 99);
    modifica_element(materii_prime, 1, materie_prima4);
    assert(((MateriePrima*)materii_prime->array[1])->cantitate == 99);
    MateriePrima* materie_prima5 = creeaza_materie_prima("m3", "p3", 99);
    assert(modifica_element(materii_prime, 5, materie_prima5) == 0);
    MateriePrima* sortat = sorteaza_materii_prime(materii_prime, compara_dupa_nume, 0);
    assert(strcmp(sortat[1].nume, "m3") == 0);
    free(sortat);
    sortat = sorteaza_materii_prime(materii_prime, compara_dupa_nume, 1);
    assert(strcmp(sortat[1].nume, "m1") == 0);
    free(sortat);
    sortat = sorteaza_materii_prime(materii_prime, compara_dupa_cantitate, 0);
    assert(sortat[1].cantitate == 99);
    free(sortat);
    sortat = sorteaza_materii_prime(materii_prime, compara_dupa_cantitate, 1);
    assert(sortat[0].cantitate == 99);
    free(sortat);
    MateriePrima* materie_prima6 = creeaza_materie_prima("m6", "p6", 4);
    adauga_element(materii_prime, materie_prima6);
    sortat = sorteaza_materii_prime_insertion(materii_prime, compara_dupa_cantitate, 0);
    assert(sortat[2].cantitate == 99);
    free(sortat);

    int total = 0;
    MateriePrima* filtered = get_materii_prime_cu_cantitate_maxima(materii_prime, 90, &total);
    assert(total == 2);
    free(filtered);
    filtered = get_materii_prime_cu_cantitate_maxima(materii_prime, 100, &total);
    assert(total == 3);
    free(filtered);
    filtered = get_materii_prime_cu_nume(materii_prime, "m1", &total);
    assert(total == 1);
    free(filtered);
    assert(sterge_element(materii_prime, 1) == 1);
    assert(materii_prime->used == 2);
    assert(sterge_element(materii_prime, -2) == 0);
    assert(sterge_element(materii_prime, 5) == 0);
    //free(materie_prima);
    //free(materie_prima2);
    distruge_materie_prima(materie_prima4);
    distruge_materii_prime(materii_prime, (DestroyFunction)distruge_materie_prima);
    printf("service passed\n");
}
void test_liste_de_liste()
{
    MateriiPrime* materii_prime;
    materii_prime = creeaza_vid();
    adauga_materie_prima(materii_prime, creeaza_materie_prima("m1","p1",99));
    adauga_materie_prima(materii_prime, creeaza_materie_prima("m1","p1",99));
    MateriiPrime* materii_prime2;
    materii_prime2 = creeaza_vid();
    MateriiPrime* undoL;
    undoL = creeaza_vid();
    adauga_materie_prima(undoL, materii_prime);
    assert(undoL->used == 1);
    adauga_materie_prima(undoL, materii_prime2);
    assert(undoL->used == 2);
    distruge_materii_prime(undoL, (DestroyFunction)distruge_lista_materii);
}

void run_all_tests()
{
    run_domain_tests();
    run_repo_tests();
    run_service_tests();
    test_liste_de_liste();
}