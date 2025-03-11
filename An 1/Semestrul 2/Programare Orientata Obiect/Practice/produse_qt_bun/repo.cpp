#include "repo.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

void Repo::citeste_fisier() {
    produse.clear();
    std::ifstream f(fisier);
    if (!f.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului pentru citire.");

    std::string linie, id_str, nume, tip, pret_str;

    while (std::getline(f, linie)) {
        std::stringstream ss(linie);

        std::getline(ss, id_str, ',');
        std::getline(ss, nume, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, pret_str, ',');

        int id = std::stoi(id_str);
        double pret = std::stod(pret_str);

        Produs produs(id, nume, tip, pret);
        produse.push_back(produs);
    }

    f.close();
}

void Repo::scrie_fisier() {
    std::ofstream g(fisier);
    if (!g.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
    for(const auto& produs: produse) {
        g << produs.get_id() << "," << produs.get_nume() << "," << produs.get_tip() << "," << produs.get_pret() << '\n';
    }
    g.close();
}



void Repo::add(const Produs& prod)
{
    for(const auto& produs: produse)
    {
        if (produs.get_id() == prod.get_id() )
            throw std::runtime_error("Exista deja un produs cu acest id!");
    }
    produse.push_back(prod);
    scrie_fisier();
}

void Repo::remove(int id)
{
    for(auto it = produse.begin(); it != produse.end(); it++)
    {
        if(it->get_id() == id)
        {
            produse.erase(it);
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Produs inexistent!");
}

void Repo::update(int id, const Produs& prod)
{
    for(auto& produs: produse)
    {
        if(produs.get_id() == id) {
            produs = prod;
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Produs inexistent!");
}

std::vector<Produs> Repo::get_all() {
    citeste_fisier();
    return produse;
}

Produs Repo::find(int id)
{
    for(const auto& produs: produse)
    {
        if(produs.get_id() == id)
            return produs;
    }
    throw std::runtime_error("Produs inexistent!");
}