#include <algorithm>
#include "service.h"

void Service::adauga(int id, std::string nume, std::string tip, double pret) {
    Produs produs{ id, nume, tip, pret };
    validator.validate_produs(produs);
    repo.add(produs);
}

void Service::sterge(int id) {
    repo.remove(id);
}

void Service::modifica(int id, std::string nume, std::string tip, double pret) {
    Produs produs{ id, nume, tip, pret };
    validator.validate_produs(produs);
    repo.update(id, produs);
}

std::vector<Produs> Service::get_all() {
    return repo.get_all();
}

int Service::get_numar_vocale(std::string nume) {
    int numar_vocale = 0;
    for (char c : nume) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            numar_vocale++;
        }
    }
    return numar_vocale;
}

std::vector<Produs> Service::sortare() {
    std::vector<Produs> produse = repo.get_all();
    std::sort(produse.begin(), produse.end(), [](const Produs &p1, const Produs &p2) {
        return p1.get_pret() < p2.get_pret();
    });
    return produse;
}

Produs Service::cauta(int id) {
    return repo.find(id);
}

std::vector<Produs> Service::filtrare(std::string tip)
{
    std::vector<Produs> produse = repo.get_all();
    std::vector<Produs> produse_filtrate;
    for(auto& produs : produse)
        if(produs.get_tip() == tip)
            produse_filtrate.push_back(produs);
    return produse_filtrate;
}

