#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

//Average case: O(1)
Multime::Multime() {
    // Constructorul multimii
    prim = nullptr;
    ultim = nullptr;
    dimensiune = 0;
}

// Best case: O(1) - când elementul apare si este primul
// Worst case: O(n) - când elementul nu exista
// Average case: O(n)
bool Multime::adauga(TElem elem) {
    // Adauga un element daca nu exista deja

    if(cauta(elem)==true)
        return false;

    Node* nod = new Node(elem);
    if (prim == nullptr) {
        prim = nod;
        ultim = nod;
    }
    else {
        ultim->urm = nod;
        nod->pred = ultim;
        ultim = nod;
    }
    dimensiune++;
    return true;
}

// Best case: O(1) - când elementul e pe prima pozitie
// Worst case: O(n) - când elementul este ultimul
// Average case: O(n)
bool Multime::sterge(TElem elem) {
    // Sterge un element daca exista
    if (cauta(elem) == true) {
        Node* nod = prim;
        for (nod = prim; nod != nullptr; nod = nod->urm) {
            if (nod->elemente == elem) {
                if (nod == prim) {
                    prim = nod->urm;
                    if (prim != nullptr) {
                        prim->pred = nullptr;
                    }
                }
                else if (nod == ultim) {
                    ultim = nod->pred;
                    ultim->urm = nullptr;
                }
                else {
                    nod->pred->urm = nod->urm;
                    nod->urm->pred = nod->pred;
                }
                delete nod;
                dimensiune--;
                return true;
            }
        }
    }
    return false;
}


// Best case: O(1) - când elementul este primul
// Worst case: O(n) - când elementul nu există
// Average case: O(n)
bool Multime::cauta(TElem elem) const {
    // Cauta un element in multime
    Node* nod = prim;
    for (nod = prim; nod != nullptr; nod = nod->urm) {
        if (nod->elemente == elem) {
            return true;
        }
    }
    return false;
}


// Average case: O(1)
int Multime::dim() const {
    // Returneaza dimensiunea multimii
    return dimensiune;
}

//Average case: O(1)
bool Multime::vida() const {
    // Verifica daca multimea e vida
    return dimensiune==0;
}

//Average case: O(n)
Multime::~Multime() {
    // Destructorul multimii
    Node* current = prim;
    while (current != nullptr) {
        Node* temp = current;
        current = current->urm;
        delete temp;
    }

    prim = nullptr;
    ultim = nullptr;
    dimensiune = 0;

}


//Average case: O(1)
IteratorMultime Multime::iterator() const {
    // Returneaza un iterator pe multime
    return IteratorMultime(*this);
}

//Best case: theta(n) cand nu trebuie sterse elemente
//Worst case: theta(n^2) cand trebuie stearsa ultima jumatate a listei
//Total: O(n^2)
void Multime::filtreaza(Conditie cond) {
    // Filtreaza elementele multimii in functie de o conditie
    Node* nod = prim;
    while (nod != nullptr) {
        Node* urmator = nod->urm;
        if (!cond(nod->elemente)) sterge(nod->elemente);

        nod = urmator;
    }
}
/*
Functie filtreaza(Cond conditie)
    nod <- prim
    Cat timp nod != NIL executa
        urmator <- [nod].urm
        Daca conditie([nod].element)=fals
            sterge([nod].element)
        nod <- urmator
    SfarsitCatTimp
SfarsitFunctie
*/



