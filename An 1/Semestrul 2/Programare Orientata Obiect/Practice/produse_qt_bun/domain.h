#pragma once
#include <string>

class Produs
{
private:
    int id;
    std::string nume;
    std::string tip;
    double pret;
public:
    int get_id() const;
    std::string get_nume() const;
    std::string get_tip() const;
    double get_pret() const;
    void set_id(int id_nou);
    void set_nume(std::string nume_nou);
    void set_tip(std::string tip_nou);
    void set_pret(double pret_nou);
    Produs(int id, std::string nume, std::string tip, double pret) : id { id }, nume { nume }, tip { tip }, pret { pret } {};
};