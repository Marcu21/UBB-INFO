#pragma once
#include <string>
using std::string;

class Produs
{
private:
    int cod;
    string denumire;
    int numar;
    double pret;
public:
    int get_cod() const;
    string get_denumire() const;
    int get_numar() const;
    double get_pret() const;
    void set_cod(int cod_nou);
    void set_denumire(string denumire_noua);
    void set_numar(int numar_nou);
    void set_pret(double pret_nou);
    Produs(int cod, string denumire, int numar, double pret): cod { cod }, denumire { denumire }, numar { numar }, pret { pret } {};
};