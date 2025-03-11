#include "domain.h"

int Produs::get_cod() const {
    //Returneaza codul
    return this->cod;
}

string Produs::get_denumire() const {
    //Returneaza denumirea
    return this->denumire;
}

int Produs::get_numar() const {
    //Returneaza numarul
    return this->numar;
}

double Produs::get_pret() const {
    //Returneaza pretul
    return this->pret;
}

void Produs::set_cod(int cod_nou) {
    //Seteaza codul
    this->cod = cod_nou;
}

void Produs::set_denumire(std::string denumire_noua) {
    //Seteaza denumire
    this->denumire = denumire_noua;
}

void Produs::set_numar(int numar_nou) {
    //Seteaza numar
    this->numar = numar_nou;
}

void Produs::set_pret(double pret_nou) {
    //Seteaza pret
    this->pret = pret_nou;
}