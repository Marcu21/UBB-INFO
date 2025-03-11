#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <stdexcept>

using namespace std;

//Complexitate: 0(1)
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d), curent(d.prim){
    //Constructorul iteratorului
}

//Complexitate: 0(1)
void IteratorDictionar::prim() {
    //Seteaza iteratorul pe primul element din dictionar
    curent = dict.prim;
}

//Complexitate: 0(1)
void IteratorDictionar::urmator() {
    //Trece la urmatorul element din dictionar
    if (!valid()) {
        throw std::exception();
    }
    curent = dict.elems[curent].urm;

}

//Complexitate: 0(1)
TElem IteratorDictionar::element() const{
    //Returneaza elementul curent din dictionar
    if (!valid()) {
        throw std::exception();
    }
    return dict.elems[curent].e;
}

//Complexitate: 0(1)
bool IteratorDictionar::valid() const {
    //Verifica daca iteratorul e valid
    return curent != -1;
}

