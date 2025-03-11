#pragma once
#include <string>
using std::string;

class Melodie
{
private:
    int id;
    string titlu;
    string artist;
    string gen;
public:
    Melodie(int id, string titlu, string artist, string gen): id{id}, titlu{titlu}, artist{artist}, gen{gen} {};
    void set_id(int id_nou);
    void set_titlu(string titlu_nou);
    void set_artist(string artist_nou);
    void set_gen(string gen_nou);
    int get_id() const;
    string get_titlu() const;
    string get_artist() const;
    string get_gen() const;

};