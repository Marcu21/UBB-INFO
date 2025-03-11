#include "domain.h"

int Utilaj::get_id() const {
    //Returneaza id-ul utilajului
    return id;
}

string Utilaj::get_denumire() const {
    //Returneaza denumirea utilajului
    return denumire;
}

string Utilaj::get_tip() const {
    //Returneaza tipul utilajului
    return tip;
}

int Utilaj::get_cilindrii() const {
    //Returneaza cilindrii utilajului

    return cilindrii;
}

void Utilaj::set_id(int id_nou) {
    //Seteaza un id nou utilajului
    id = id_nou;
}

void Utilaj::set_denumire(std::string denumire_noua) {
    //Seteaza o denumire noua utilajului

    denumire = denumire_noua;
}

void Utilaj::set_tip(std::string tip_nou) {
    //Seteaza un tip nou utilajului
    tip = tip_nou;
}

void Utilaj::set_cilindrii(int cilindrii_nou) {
    //Seteaza cilindrii noi utilajului
    cilindrii = cilindrii_nou;
}