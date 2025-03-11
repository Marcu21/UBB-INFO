#include "locatar.h"

int Locatar::get_apartament() const
{
    //Returneaza apartamentul
    return apartament;
}

int Locatar::get_suprafata() const
{
    //Returneaza suprafata
    return suprafata;
}

string Locatar::get_nume_proprietar() const
{
    //Returneaza numele proprietarului
    return nume_proprietar;
}

string Locatar::get_tip_apartament() const
{
    //Returneaza tipul apartamentului
    return tip_apartament;
}

void Locatar::set_apartament(int ap)
{
    //Seteaza apartamentul
    this->apartament = ap;
}

void Locatar::set_suprafata(int sup)
{
    //Seteaza suprafata
    this->suprafata = sup;
}

void Locatar::set_nume_proprietar(const string& nume)
{
    //Seteaza numele proprietarului
    this->nume_proprietar = nume;
}

void Locatar::set_tip_apartament(const string& tip)
{
    //Seteaza tipul apartamentului
    this->tip_apartament = tip;
}

Locatar Locatar::creeaza_locatar(Locatar locatar, int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament)
{
    // Creeaza un locatar
    locatar.set_apartament(apartament);
    locatar.set_nume_proprietar(nume_proprietar);
    locatar.set_suprafata(suprafata);
    locatar.set_tip_apartament(tip_apartament);
    return locatar;
}
