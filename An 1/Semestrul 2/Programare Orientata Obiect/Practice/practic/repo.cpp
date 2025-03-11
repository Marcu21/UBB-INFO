#include <fstream>
#include "repo.h"
#include <stdexcept>

void Repo::citeste_fisier() {
    //Citeste din fisier
    utilaje.clear();
    std::ifstream f(fisier);
    int id, cilindrii;
    string denumire, tip;
    while(f>>id>>denumire>>tip>>cilindrii)
    {
        utilaje.push_back(Utilaj{id, denumire, tip, cilindrii});
    }
    f.close();
}

void Repo::scrie_fisier() {
    //Scrie in fisier
    std::ofstream f(fisier);
    for(const auto& elem:utilaje)
    {
        f<<elem.get_id()<<' '<<elem.get_denumire()<<' '<<elem.get_tip()<<' '<<elem.get_cilindrii()<<'\n';
    }
    f.close();
}

void Repo::add(Utilaj u) {
    //Adauga un utilaj
    for(const auto& elem: utilaje)
    {
        if(elem.get_id() == u.get_id()) throw std::runtime_error("Utilajul cu acest id exista deja!");
    }
    utilaje.push_back(u);
    scrie_fisier();
}

void Repo::modify(int id, const Utilaj& u) {

    //Modifica un utilaj
    for (Utilaj& ut : utilaje) {
        if (ut.get_id() == id) {
            ut.set_denumire(u.get_denumire());
            ut.set_tip(u.get_tip());
            ut.set_cilindrii(u.get_cilindrii());
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Nu exista utilajul cu acest id!");
}

void Repo::remove(int id) {
    //Sterge un utilaj
    for(auto it = utilaje.begin(); it!=utilaje.end();it++)
    {
        if(it->get_id() == id)
        {
            utilaje.erase(it);
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Nu exista utilajul cu acest id!");
}

Utilaj Repo::find(int id) {
    //Cauta un utilaj
    for(const auto& elem: utilaje)
    {
        if(elem.get_id() == id) return elem;
    }
    throw std::runtime_error("Nu exista utilajul cu acest id!");
}

vector<Utilaj> Repo::get_all() {
    //Returneaza lista de utilaje
    citeste_fisier();
    return utilaje;
}