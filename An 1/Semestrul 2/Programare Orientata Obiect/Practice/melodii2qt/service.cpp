#include "service.h"
#include "validator.h"

void Service::adauga(int id, std::string titlu, std::string artist, std::string gen) {
    Melodie melodie{id, titlu, artist, gen};
    Validator::validate(melodie);
    repo.add(melodie);
}

void Service::sterge(int id) {
    repo.destroy(id);
}

void Service::modifica(int id, std::string titlu, std::string artist, std::string gen) {
    Melodie melodie{id, titlu, artist, gen};
    Validator::validate(melodie);
    repo.modify(id, melodie);
}

Melodie Service::cauta(int id) {
    return repo.find(id);
}

vector<Melodie> Service::get_all() {
    return repo.get_all();
}

vector<Melodie> Service::sortare() {
    vector<Melodie> rez = repo.get_all();
    for(int i = 0; i < rez.size()-1;i++)
    {
        for(int  j = i+1; j< rez.size();j++)
        {
            if(rez[i].get_artist()>rez[j].get_artist()) std::swap(rez[i],rez[j]);
        }
    }
    return rez;
}