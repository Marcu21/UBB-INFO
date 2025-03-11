#pragma once
#include "repo.h"

class Service
{
private:
    Repo& repo;
public:
    Service(Repo& repo): repo{repo} {};
    void adauga(int id, string titlu, string artist, string gen);
    void sterge(int id);
    void modifica(int id, string titlu, string artist, string gen);
    Melodie cauta(int id);
    vector<Melodie> get_all();
    vector<Melodie> sortare();
};
