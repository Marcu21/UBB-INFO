#pragma once
#include "domain.h"
#include <vector>
using std::vector;

class Repo
{
private:
    vector<Melodie> melodii;
    string fisier;
    void scrie_fisier();
    void citeste_fisier();
public:
    Repo(string nume_fisier): fisier{nume_fisier} {};
    void add(Melodie m);
    void destroy(int id);
    void modify(int id, Melodie m);
    vector<Melodie> get_all();
    Melodie find(int id);
    void goleste();
};