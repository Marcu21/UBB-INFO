#include "domain.h"

int Produs::get_id() const
{
    return int(id);
}

std::string Produs::get_nume() const {
    return nume;
}

std::string Produs::get_tip() const {
    return tip;
}

double Produs::get_pret() const
{
    return double(pret);
}

void Produs::set_id(int id_nou)
{
    this->id = id_nou;
}

void Produs::set_nume(std::string nume_nou) {
    this-> nume = nume_nou;
}

void Produs::set_tip(std::string tip_nou) {
    this->tip = tip_nou;
}

void Produs::set_pret(double pret_nou) {
    this->pret = pret_nou;
}