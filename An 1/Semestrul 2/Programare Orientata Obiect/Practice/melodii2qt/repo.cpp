#include "repo.h"
#include <fstream>
#include <sstream>

void Repo::citeste_fisier() {
    melodii.clear();
    std::ifstream f(fisier);
    if (!f.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului pentru citire.");

    std::string linie, id_str, nume, tip, pret;

    while (std::getline(f, linie)) {
        std::stringstream ss(linie);

        std::getline(ss, id_str, ',');
        std::getline(ss, nume, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, pret, ',');

        int id = std::stoi(id_str);

        Melodie melodie(id, nume, tip, pret);
        melodii.push_back(melodie);
    }

    f.close();
}

void Repo::scrie_fisier() {
    std::ofstream g(fisier);
    if (!g.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
    for(auto& melodie: melodii) {
        g << melodie.get_id() << "," << melodie.get_titlu() << "," << melodie.get_artist() << "," << melodie.get_gen() << '\n';
    }
    g.close();
}

/*void Repo::add(Melodie m) {
    int k = 0, id;
    srand(time(NULL));
    while(k==0)
    {
        k = 1;
        id = rand();
        for(auto melodie:melodii)
        {
            if(melodie.get_id() == id) k = 0;
        }
    }
    m.set_id(id);
    melodii.push_back(m);
    scrie_fisier();
}*/

void Repo::add(Melodie m) {
    for(auto melodie:melodii)
    {
        if(melodie.get_id() == m.get_id())
            throw std::runtime_error("Melodie existenta!");
    }
    melodii.push_back(m);
    scrie_fisier();
}

void Repo::destroy(int id) {
    for(auto it = melodii.begin(); it!=melodii.end(); it++)
    {
        if(it->get_id() == id) {
            melodii.erase(it);
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Melodie inexistenta!");
}

void Repo::modify(int id, Melodie m) {
    for(auto &melodie: melodii)
    {
        if(melodie.get_id() == id)
        {
            melodie = m;
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Melodie inexistenta!");
}

Melodie Repo::find(int id) {
    for(auto melodie:melodii)
    {
        if(melodie.get_id() == id) return melodie;
    }
    throw std::runtime_error("Melodie inexistenta!");
}

vector<Melodie> Repo::get_all() {
    citeste_fisier();
    return melodii;
}

void Repo::goleste() {
    melodii.clear();
    scrie_fisier();
}