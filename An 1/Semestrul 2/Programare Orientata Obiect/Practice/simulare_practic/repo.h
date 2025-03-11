#pragma once
#include <string>
#include <vector>
#include "domain.h"
using std::vector;
using std::string;

class Repo
{
private:
    string fisier = "C:\\Users\\emanu\\CLionProjects\\simulare_practic\\produse.txt";
    void citeste_fisier();
    void scrie_fisier();
    vector<Produs> produse;
public:
    void add(Produs prod);
    void find(int cod);
    void destroy(int cod);
    void modify(int cod);
    vector<Produs> get_all();
};