#pragma once
#include <string>
using std::string;

class Utilaj
{
private:
    int id;
    string denumire;
    string tip;
    int cilindrii;
public:
    Utilaj(int id, string denumire, string tip, int cilindrii): id{id}, denumire{denumire}, tip{tip}, cilindrii{cilindrii} {};
    void set_id(int id_nou);
    void set_denumire(string denumire_noua);
    void set_tip(string tip_nou);
    void set_cilindrii(int cilindrii_nou);
    int get_id() const;
    string get_denumire() const;
    string get_tip() const;
    int get_cilindrii() const;

};