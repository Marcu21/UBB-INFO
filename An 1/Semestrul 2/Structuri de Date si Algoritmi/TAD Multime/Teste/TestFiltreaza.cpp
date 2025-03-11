#include "Multime.h"
#include <assert.h>
bool estePar(TElem e) {
    return e % 2 == 0;
}

bool esteImpar(TElem e) {
    return e % 2 != 0;
}
void testFiltreaza() {
    Multime m;

    m.adauga(1);
    m.adauga(2);
    m.adauga(3);
    m.adauga(4);
    m.adauga(11);
    m.adauga(12);
    m.adauga(13);

    m.filtreaza(estePar);
    assert(m.dim() == 3);
    assert(m.cauta(2) && m.cauta(12) && m.cauta(4));
    assert(!m.cauta(1) && !m.cauta(3) && !m.cauta(11) && !m.cauta(13));

    m = Multime();
    m.adauga(1);
    m.adauga(2);
    m.adauga(3);
    m.adauga(4);
    m.adauga(11);
    m.adauga(12);
    m.adauga(13);
    m.filtreaza(esteImpar);
    assert(m.dim() == 4);
    assert(m.cauta(1) && m.cauta(3) && m.cauta(11) && m.cauta(13));
    assert(!m.cauta(2) && !m.cauta(12) && !m.cauta(4));
}