#include <stdexcept>
#include "service.h"

void Service::adauga(int id, std::string denumire, std::string tip, int cilindrii) {
    //Valideaza si adauga un utilaj
    Utilaj u(id, denumire, tip, cilindrii);
    validator.validate(u);
    repo.add(u);
}

void Service::modifica(int id, std::string denumire, std::string tip, int cilindrii) {
    //Valideaza si modifica un utilaj
    Utilaj u(id, denumire, tip, cilindrii);
    validator.validate(u);
    repo.modify(id, u);
}

/*void Service::sterge(int id) {
    //Sterge un utilaj
    int k = 0, cil = -1;
    int nr = 0;
    for(auto &elem: get_all())
    {
        if(elem.get_id() == id)
        {
            k = 1;
            cil = elem.get_cilindrii();
        }
        else if(elem.get_cilindrii() == cil && k == 1)
        {
            nr++;
        }
    }
    if(nr > 0) repo.remove(id);
    else throw std::runtime_error("Este ultimul utilaj cu acest nr de cilindri!");
}*/

void Service::sterge(int id) {
    //Sterge un utilaj
    int cil = cauta(id).get_cilindrii();
    int nr = 0;
    for(auto &elem: get_all())
    {
        if(elem.get_cilindrii() == cil)
        {
            nr++;
        }
    }
    if(nr > 1) repo.remove(id);
    else throw std::runtime_error("Este ultimul utilaj cu acest nr de cilindri!");
}

Utilaj Service::cauta(int id) {
    //Cauta un utilaj
    return repo.find(id);
}

vector<Utilaj> Service::get_all() {
    //Returneaza lista de utilaje
    return repo.get_all();
}

vector<Utilaj> Service::get_all_sortat() {
    //Returneaza lista sortata de utilaje
    vector<Utilaj> rez = get_all();
    for(int i = 0; i < rez.size() - 1; i++)
    {
        for(int j = i + 1; j < rez.size(); j++)
        {
            if(rez[i].get_tip() > rez[j].get_tip()) std::swap(rez[i], rez[j]);
            else if(rez[i].get_tip() == rez[j].get_tip())
                if(rez[i].get_denumire() > rez[j].get_denumire()) std::swap(rez[i], rez[j]);
        }
    }
    return rez;}