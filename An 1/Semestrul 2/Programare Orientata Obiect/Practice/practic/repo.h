#pragma once
#include "domain.h"
#include <vector>
using std::vector;

class Repo
{
private:
    vector<Utilaj> utilaje;
    string fisier = "C:\\Users\\emanu\\CLionProjects\\practic\\fisier";
    void scrie_fisier();
    void citeste_fisier();
public:
    Repo() = default;
    void add(Utilaj u);
    void remove(int id);
    void modify(int id, const Utilaj& u);
    Utilaj find(int id);
    vector<Utilaj> get_all();
};