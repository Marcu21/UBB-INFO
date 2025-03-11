#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>

using std::vector;

class Repo
{
private:
    vector<Melodie> melodii;
    string fisier = "C:\\Users\\emanu\\CLionProjects\\melodii1\\melodii.txt";
    void citeste_fisier();
    void scrie_fisier();
public:
    void add(const Melodie& melodie);
    void remove(int id);
    void update(int id, const Melodie& melodie);
    Melodie find(int id);
    vector<Melodie> get_all();
};