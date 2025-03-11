#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
    Matrice m(4,4);
    assert(m.nrLinii() == 4);
    assert(m.nrColoane() == 4);
    //adaug niste elemente
    m.modifica(1,1,5);
    assert(m.element(1,1) == 5);
    m.modifica(1,1,6);
    assert(m.element(1,2) == NULL_TELEMENT);
}

void testNou()
{
    Matrice m(4, 4);
    assert(m.nrLinii() == 4);
    assert(m.nrColoane() == 4);

    m.modifica(1, 1, 5);
    assert(m.element(1, 1) == 5);
    assert(m.element(1, 2) == NULL_TELEMENT);

    assert(m.numarElementeNenule(1) == 1);

    m.modifica(1, 2, 7);
    m.modifica(1, 3, 8);
    assert(m.numarElementeNenule(1) == 3);

    m.modifica(1, 1, NULL_TELEMENT);
    assert(m.numarElementeNenule(1) == 2);

    assert(m.numarElementeNenule(0) == 0);
    assert(m.numarElementeNenule(2) == 0);
    assert(m.numarElementeNenule(3) == 0);

    try {
        m.numarElementeNenule(-1);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(true);
    }

    try {
        m.numarElementeNenule(4);
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(true);
    }
}

void testValoareMaxima()
{
    Matrice m(4, 4);
    assert(m.valoareMaxima() == NULL_TELEMENT);

    m.modifica(1, 1, 5);
    assert(m.valoareMaxima() == 5);

    m.modifica(1, 2, 7);
    assert(m.valoareMaxima() == 7);

    m.modifica(1, 3, 8);
    assert(m.valoareMaxima() == 8);

    m.modifica(1, 1, 10);
    assert(m.valoareMaxima() == 10);

    m.modifica(1, 1, NULL_TELEMENT);
    assert(m.valoareMaxima() == 8);

    m.modifica(1, 3, NULL_TELEMENT);
    assert(m.valoareMaxima() == 7);

    m.modifica(1, 2, NULL_TELEMENT);
    assert(m.valoareMaxima() == NULL_TELEMENT);
}
