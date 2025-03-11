#pragma once
#include "repo.h"
#include "validator.h"

class Service
{
private:
    Repo repo;
    Validator validator;
public:
    Service(Repo repo, Validator validator): repo{repo}, validator{validator} {};
    void adauga(int id, string denumire, string tip, int cilindrii);
    void sterge(int id);
    void modifica(int id, string denumire, string tip, int cilindrii);
    Utilaj cauta(int id);
    vector<Utilaj> get_all();
    vector<Utilaj> get_all_sortat();
};