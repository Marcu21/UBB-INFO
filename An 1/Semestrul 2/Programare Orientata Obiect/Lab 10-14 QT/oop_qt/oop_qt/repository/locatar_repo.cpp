#include "locatar_repo.h"
#include "../domain/locatar.h"
#include "../validators/exception.h"
#include <algorithm>

void locatar_repo::store(const Locatar& locatar) {
    //Adauga un locatar in lista de locatari
    for (const Locatar& l : locatari)
        if (l.get_apartament() == locatar.get_apartament() && l.get_nume_proprietar() == locatar.get_nume_proprietar())
            throw repo_exception("Locatar deja existent!");
    locatari.push_back(locatar);
}

std::vector<Locatar>& locatar_repo::get_all(){
    //Returneaza lista de locatari
    return locatari;
}

void locatar_repo::destroy(int apartament, const string& nume_proprietar) {
    // Sterge un locatar din lista de locatari
    auto it = std::find_if(locatari.begin(), locatari.end(), [&](const Locatar& l) {
        return l.get_apartament() == apartament && l.get_nume_proprietar() == nume_proprietar;
    });

    if (it != locatari.end()) {
        locatari.erase(it);
    } else {
        throw repo_exception("Locatar inexistent!");
    }
}


void locatar_repo::modify(int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament) {
    //Modifica un locatar din lista de locatari
    for (auto& locatar : locatari) {
        if (locatar.get_apartament() == apartament) {
            locatar.set_nume_proprietar(nume_proprietar);
            locatar.set_suprafata(suprafata);
            locatar.set_tip_apartament(tip_apartament);
            return;
        }
    }
    throw repo_exception("Locatar inexistent!");
}


Locatar locatar_repo::find(int apartament)
{
    //Cauta un locatar in lista de locatari
    auto it = std::find_if(locatari.begin(), locatari.end(), [apartament](const Locatar& locatar) {
        return locatar.get_apartament() == apartament;
    });

    if (it != locatari.end()) {
        return *it;
    } else {
        throw repo_exception("Locatar inexistent!");
    }
}



void repo_dictionar::store(const Locatar& locatar) {
    //Adauga un locatar in dictionarul de locatari
    const double store_probability = 0.5;
    if (probabilitate < store_probability)
        throw std::runtime_error("Probabilitatea nu este buna!");

    auto it = locatari.find(locatar.get_apartament());
    if (it != locatari.end())
        throw std::runtime_error("Locatar deja existent!");

    locatari[locatar.get_apartament()] = locatar;
}

std::vector<Locatar>& repo_dictionar::get_all() {
    //Returneaza toti locatarii
    const double get_all_probability = 0.4;
    if (probabilitate < get_all_probability)
        throw std::runtime_error("Probabilitatea nu este buna!");

    locatari_vector.clear();
    for (const auto& pair : locatari) {
        locatari_vector.push_back(pair.second);
    }
    return locatari_vector;
}


void repo_dictionar::destroy(int apartament, const std::string& nume_proprietar) {
    //Sterge un locatar
    const double destroy_probability = 0.6;
    if (probabilitate < destroy_probability) throw std::runtime_error("Probabilitatea nu este buna!");

    auto it = locatari.find(apartament);
    if (it == locatari.end() || it->second.get_nume_proprietar() != nume_proprietar) throw std::runtime_error("Locatar inexistent!");

    locatari.erase(it);
}

void repo_dictionar::modify(int apartament, const std::string& nume_proprietar, int suprafata, const std::string& tip_apartament) {
    //Modifica un locatar
    const double modify_probability = 1.0;
    if (probabilitate < modify_probability) throw std::runtime_error("Probabilitatea nu este buna!");

    auto it = locatari.find(apartament);
    if (it == locatari.end() || it->second.get_nume_proprietar() != nume_proprietar) throw std::runtime_error("Locatar inexistent!");

    it->second.set_nume_proprietar(nume_proprietar);
    it->second.set_suprafata(suprafata);
    it->second.set_tip_apartament(tip_apartament);
}

Locatar repo_dictionar::find(int apartament) {
    //Cauta un locatar
    const double find_probability = 0.8;
    if (probabilitate < find_probability) throw std::runtime_error("Probabilitatea nu este buna!");

    auto it = locatari.find(apartament);
    if (it != locatari.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Locatar inexistent!");
    }
}
