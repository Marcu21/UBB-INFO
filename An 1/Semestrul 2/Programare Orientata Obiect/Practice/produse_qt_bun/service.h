#pragma once
#include "repo.h"
#include <vector>
#include <string>
#include "validator.h"
class Service
{
private:
    Repo repo;
    Validator validator;
public:
    Service( Repo repo, Validator validator ) : repo { repo }, validator { validator } {};
    void adauga( int id, std::string nume, std::string tip, double pret );
    void sterge( int id );
    void modifica( int id, std::string nume, std::string tip, double pret );
    std::vector<Produs> get_all();
    int get_numar_vocale( std::string nume );
    std::vector<Produs> sortare();
    Produs cauta(int id);
    std::vector<Produs> filtrare(std::string tip);
};
