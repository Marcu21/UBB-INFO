#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;

class Locatar
{
private:
    int apartament;
    string nume_proprietar;
    int suprafata;
    string tip_apartament;
public:
    [[nodiscard]] int get_apartament() const;
    [[nodiscard]] int get_suprafata() const;
    [[nodiscard]] string get_nume_proprietar() const;
    [[nodiscard]] string get_tip_apartament() const;
    void set_apartament(int apartament);
    void set_suprafata(int suprafata);
    void set_nume_proprietar(const string& nume_proprietar);
    void set_tip_apartament(const string& tip_apartament);
    static Locatar creeaza_locatar(Locatar locatar, int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament);
    Locatar(const Locatar& locatar) = default;
    Locatar() : apartament(0), nume_proprietar(), suprafata(0), tip_apartament() {cout<<"*\n";}
};