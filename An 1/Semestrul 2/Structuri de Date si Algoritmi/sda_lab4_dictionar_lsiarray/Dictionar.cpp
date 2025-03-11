#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

//0(n)
Dictionar::Dictionar() : prim(-1), liber(0), capacitate(10) {
    //Constructorul dictionarului
    elems = new Nod[capacitate];
    for (int i = 0; i < capacitate - 1; i++) {
        elems[i].urm = i + 1;
    }
    elems[capacitate - 1].urm = -1;
}

//0(1)
Dictionar::~Dictionar() {
    //Destructorul dictionarului
    delete[] elems;
}


//Best case: 0(1) - daca cheia exista deja pe prima pozitie
//Worst case: 0(n) - daca cheia nu exista in dictionar
//Total complexity: O(n)
TValoare Dictionar::adauga(TCheie c, TValoare v){
    //Adauga o pereche in dictionar
    int curent = prim;
    while (curent != -1 && elems[curent].e.first != c) {
        curent = elems[curent].urm;
    }

    if (curent != -1) {
        TValoare veche = elems[curent].e.second;
        elems[curent].e.second = v;
        return veche;
    }

    if (liber == -1) {
        resize();
    }

    int nou = liber;
    liber = elems[liber].urm;

    elems[nou].e = {c, v};
    elems[nou].urm = prim;
    prim = nou;

    return NULL_TVALOARE;

}

//0(n)
void Dictionar::resize() {
    //Redimensioneaza dictionarul
    int nouaCapacitate = 2 * capacitate;
    Nod* nouElems = new Nod[nouaCapacitate];
    for (int i = 0; i < capacitate; i++) {
        nouElems[i] = elems[i];
    }
    for (int i = capacitate; i < nouaCapacitate - 1; i++) {
        nouElems[i].urm = i + 1;
    }
    nouElems[nouaCapacitate - 1].urm = -1;
    liber = capacitate;
    capacitate = nouaCapacitate;
    delete[] elems;
    elems = nouElems;
}

//Best case: 0(1) - daca cheia exista pe prima pozitie
//Worst case: 0(n) - daca cheia nu exista in dictionar
//Total complexity: O(n)
TValoare Dictionar::cauta(TCheie c) const{
    //Cauta o cheie si returneaza valoarea asociata
    int curent = prim;
    while (curent != -1) {
        if (elems[curent].e.first == c) {
            return elems[curent].e.second;
        }
        curent = elems[curent].urm;
    }
    return NULL_TVALOARE;
}


//Best case: 0(1) - daca cheia exista pe prima pozitie
//Worst case: 0(n) - daca cheia nu exista in dictionar
//Total complexity: O(n)
TValoare Dictionar::sterge(TCheie c){
    //Sterge o cheie si returneaza valoarea asociata
    int curent = prim;
    int precedent = -1;
    while (curent != -1 && elems[curent].e.first != c) {
        precedent = curent;
        curent = elems[curent].urm;
    }

    if (curent == -1) {
        return NULL_TVALOARE;
    }

    if (precedent == -1) {
        prim = elems[curent].urm;
    } else {
        elems[precedent].urm = elems[curent].urm;
    }

    TValoare valoareVeche = elems[curent].e.second;
    elems[curent].urm = liber;
    liber = curent;

    return valoareVeche;

}

//0(n)
int Dictionar::dim() const {
    //Returneaza numarul de perechi din dictionar
    int cnt = 0;
    int curent = prim;
    while (curent != -1) {
        cnt++;
        curent = elems[curent].urm;
    }
    return cnt;

}

//0(1)
bool Dictionar::vid() const{
    //Verifica daca dictionarul e vid
    return prim == -1;
}

//0(1)
IteratorDictionar Dictionar::iterator() const {
    //Returneaza iterator pe dictionar
    return  IteratorDictionar(*this);
}

//Best case: 0(m^2), m<n daca toate elementele din dictionarul d sunt in dictionarul nostru
//Worst case: 0(n(n+m)) daca niciun element din dictionarul d nu este in dictionarul nostru
//Total complexity: O(n^2*m)
int Dictionar::adaugaInexistente(Dictionar& d) {
    //Adauga in dictionarul curent toate perechile din dictionarul d care nu sunt prezente in dictionarul nostru
    int count = 0;

    IteratorDictionar it = d.iterator();

    for (it.prim(); it.valid(); it.urmator()) {
        TElem elem = it.element();
        TCheie c = elem.first;
        TValoare v = elem.second;

        if (cauta(c) == NULL_TVALOARE) {
            adauga(c, v);
            count++;
        }
    }

    return count;
}


/*
Functie adaugaInexistente
    count <- 0
    it <- d.iterator()
    Pentru it.prim() pana cand it.valid(), it.urmator() executa
        elem <- it.element()
        c <- elem.first()
        v <- elem.second()
        Daca cauta(c) == NULL_TVALOARE atunci
            adauga(c,v)
            count <- count + 1
        SfDaca
    SfPentru
    return count
Sf Functie
 */