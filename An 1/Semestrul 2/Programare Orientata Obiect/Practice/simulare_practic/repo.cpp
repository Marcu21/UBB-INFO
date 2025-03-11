#include "repo.h"
#include <stdexcept>
#include <sstream>
#include <fstream>

vector<Produs> Repo::get_all() {
    //Returneaza produsele
    citeste_fisier();
    return produse;
}

void Repo::add(Produs prod) {
    //Adauga un produs, arunca exceptie daca exista deja unul cu id-ul respectiv
    for(auto& produs: produse)
    {
        if(produs.get_cod() == prod.get_cod())
            throw std::runtime_error("Exista deja un produs cu id-ul respectiv!");
    }
    produse.push_back(prod);
    scrie_fisier();
}

void Repo::citeste_fisier() {
    //citeste din fisier
    produse.clear();
    std::ifstream f(fisier);
    if (!f.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului pentru citire.");

    std::string linie, cod_str, denumire, numar_str, pret_str;

    while (std::getline(f, linie)) {
        std::stringstream ss(linie);

        std::getline(ss, cod_str, ',');
        std::getline(ss, denumire, ',');
        std::getline(ss, numar_str, ',');
        std::getline(ss, pret_str, ',');

        int cod = std::stoi(cod_str);
        int numar = std::stoi(numar_str);
        double pret = std::stod(pret_str);

        Produs produs(cod, denumire, numar, pret);
        produse.push_back(produs);
    }

    f.close();
}

void Repo::scrie_fisier() {
    //scrie in fisier
    std::ofstream g(fisier);
    if (!g.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
    for(const auto& produs: produse) {
        g << produs.get_cod() << "," << produs.get_denumire() << "," << produs.get_numar() << "," << produs.get_pret() << '\n';
    }
    g.close();
}

void Repo::modify(int cod)
//Modifica produsul
{
    for(auto& elem: produse)
    {
        if(elem.get_cod()==cod)
            elem.set_numar(elem.get_numar()-1);
    }
    scrie_fisier();
}