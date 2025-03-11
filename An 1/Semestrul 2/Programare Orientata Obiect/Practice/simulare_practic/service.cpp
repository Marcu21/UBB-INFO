#include "service.h"
#include <stdexcept>
#include <algorithm>

void Service::adauga(int cod, std::string denumire, int numar, double pret) {
    //Adauga un produs
    Produs prod(cod, denumire, numar, pret);
    repo.add(prod);
}

vector<Produs> Service::get_all() {
    //Returneaza lista de produse
    return repo.get_all();
}

Produs Service::cauta(int cod) {
    //Cauta un produs
    vector<Produs> lista = repo.get_all();
    for(auto& elem: lista)
    {
        if(elem.get_cod()==cod)
            return elem;
    }
    throw std::runtime_error("Nu exista produs cu acest cod!");
}

vector<Produs> Service::sortare_pret() {
    //Sorteaza lista de produse dupa pret
    vector<Produs> produse = repo.get_all();

    std::sort(produse.begin(), produse.end(), [](const Produs& a, const Produs& b) {
        return a.get_pret() < b.get_pret();
    });
    return produse;
}

vector<Produs> Service::sortare_numar() {
    //Sorteaza lista de produse dupa numar
    vector<Produs> produse = repo.get_all();

    std::sort(produse.begin(), produse.end(), [](const Produs& a, const Produs& b) {
        return a.get_numar() < b.get_numar();
    });
    return produse;
}



int Service::raport(int cod)
{
    //Returneaza numarul, arucna exceptie daca este 0
    vector<Produs> lista = repo.get_all();
    Produs prod = cauta(cod);
    if(prod.get_numar()==0) throw std::runtime_error("Numarul este 0!");
    return prod.get_numar();
}

void Service::cumparare(int cod) {
    //Cumpara un produs daca este disponibil, arunca exceptie altfel
    vector<Produs> lista = repo.get_all();
    Produs prod = cauta(cod);
    if(prod.get_numar() == 0 )
        throw std::runtime_error("Produsul nu se poate cumpara!");
    repo.modify(cod);
}