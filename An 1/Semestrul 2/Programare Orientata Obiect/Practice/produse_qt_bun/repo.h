#pragma once
#include <string>
#include "domain.h"
#include <vector>

class Repo
{
private:
    void citeste_fisier();
    void scrie_fisier();
    std::string fisier = "C:\\Users\\emanu\\CLionProjects\\produse_qt_bun\\test.txt";
    std::vector<Produs> produse;
public:
    void add(const Produs& produs);
    void remove(int id);
    void update(int id, const Produs& produs_nou);
    std::vector<Produs> get_all();
    Produs find(int id);
};