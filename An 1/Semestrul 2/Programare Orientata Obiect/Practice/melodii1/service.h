#pragma once
#include "repo.h"
#include <algorithm>
#include <vector>
#include <fstream>

class Service
{
private:
    Repo& repo;
public:
    Service(Repo& repo) : repo{ repo } {};
    void adauga(int id, string titlu, string artist, int rank);
    void sterge(int id);
    void modifica(int id, string titlu, string artist, int rank);
    Melodie cauta(int id);
    vector<Melodie> get_all();
    vector<Melodie> sortare_rank();
    int frecventa_rank(int rank);
    vector<Melodie> get_all_sorted_by_rank();

};