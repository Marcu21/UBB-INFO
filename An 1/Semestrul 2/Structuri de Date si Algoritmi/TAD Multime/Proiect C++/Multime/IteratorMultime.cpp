#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

//Average case: O(1)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
    //Initializam iteratorul multimii
    poz = 0;
}

//Average case: O(1)
void IteratorMultime::prim() {
    //Setam pozitia iteratorului la inceputul multimii
    poz = 0;
}

//Average case: O(1)
void IteratorMultime::urmator() {
    //Incrementam pozitia iteratorului
    poz++;
}

//Best case: O(1) - când iteratorul este invalid
//Worst case: O(n) - când iteratorul este valid
//Average case: O(n)
TElem IteratorMultime::element() const {
    //Returnam elementul de pe pozitia iteratorului daca pozitia este valida
    if (valid())
    {
        int i = 0;
        Multime::Node* nod = multime.prim;
        while (i < poz)
        {
            nod = nod->urm;
            i++;
        }
        return nod->elemente;
    }
    else
        throw std::exception();
}

//Average case: O(1)
bool IteratorMultime::valid() const {
    //Verificam daca pozitia iteratorului este valida
    if(poz < multime.dim())
        return true;

    return false;
}
