#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>
#include <algorithm>

// Teta(1)
AB::AB() {
    this->radacina = NULL;
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
AB::AB(const AB& ab) {
    this->radacina = copiere(ab.radacina);
}

// Teta(1)
AB::AB(TElem e){
    this->radacina = new Nod(e, NULL, NULL);
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
AB::AB(const AB& st, TElem e, const AB& dr){
    this->radacina = new Nod(e, copiere(st.radacina), copiere(dr.radacina));
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
PNod AB::copiere(PNod p) const {
    if (p != NULL) {
        //creez radacina
        PNod pNew = new Nod(p->element, NULL, NULL);
        pNew->st = copiere(p->st);
        pNew->dr = copiere(p->dr);
        return pNew;
    }
    return NULL;
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
void AB::distrugeSubarbori(PNod p) {
    if (p != NULL) {
        distruge(p->st);
        distruge(p->dr);
    }
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
void AB::distruge(PNod p) {
    if (p != NULL) {
        distruge(p->st);
        distruge(p->dr);
        delete p;
    }
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
void AB::adaugaSubSt(const AB& st){
    if (this->vid())
        throw(exception());
    // distrug vechii subarbori ai subarborelui stang
    distrugeSubarbori(this->radacina->st);
    //copiez noul subarbore
    this->radacina->st = copiere(st.radacina);
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
void AB::adaugaSubDr(const AB& dr){
    if (this->vid())
        throw(exception());
    // distrug vechii subarbori ai subarborelui drept
    distrugeSubarbori(this->radacina->dr);
    //copiez noul subarbore
    this->radacina->dr = copiere(dr.radacina);
}

// Teta(1)
TElem AB::element() const{
    if (this->vid())
        throw(exception());
    return this->radacina->element;
}

// Teta(1)
AB AB::stang() const{
    if (this->vid())
        throw(exception());
    AB ab;
    ab.radacina = copiere(this->radacina->st);
    return ab;
}

// Teta(1)
AB AB::drept() const{
    if (this->vid())
        throw(exception());
    AB ab;
    ab.radacina = copiere(this->radacina->dr);
    return ab;
}

// caz favoranil : Teta(1)
// caz defavorabil : Teta(n)
// overall case : O(n)
AB::~AB() {
    distruge(this->radacina);
}

// Teta(1)
bool AB::vid() const{
    return this->radacina == NULL;
}

// Teta(1)
IteratorAB* AB::iterator(string s) const {
    if (s=="preordine")
        return new IteratorPreordine(*this);
    if (s=="inordine")
        return new IteratorInordine(*this);
    if (s=="postordine")
        return new IteratorPostordine(*this);
    if (s=="latime")
        return new IteratorLatime(*this);
    return nullptr;
};

//best case: Teta(1)
//worst case: Teta(n)
//total case: O(n)
int AB::valoareMaxima() const {
    //gaseste si returneaza valoarea maxima din arbore
    //daca arborele este vid, returneaza NULL
    if (this->vid()) {
        return NULL;
    }
    return valoareMaximaHelper(this->radacina);
}

//best case: Teta(1)
//worst case: Teta(n)
//total case: O(n)
int AB::valoareMaximaHelper(PNod nod) const {
    //functie auxiliara recursiva pentru a gasi valoarea maxima din arbore
    if (nod == NULL) {
        return INT_MIN;
    }
    int maxSt = valoareMaximaHelper(nod->st);
    int maxDr = valoareMaximaHelper(nod->dr);
    return max({nod->element, maxSt, maxDr});
}



