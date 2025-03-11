#include "repo.h"

class Service
{
private:
    Repo& repo;
public:
    Service(Repo& repo): repo { repo } {};
    vector<Produs> get_all();
    void adauga(int cod, string denumire, int numar, double pret);
    Produs cauta(int cod);
    vector<Produs> sortare_pret();
    vector<Produs> sortare_numar();
    vector<Produs> nesortat();
    int raport(int cod);
    void cumparare(int cod);
};