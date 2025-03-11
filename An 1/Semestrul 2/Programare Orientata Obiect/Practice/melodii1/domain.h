#pragma once

#include <string>
using std::string;

class Melodie
{
private:
    int id;
    string titlu;
    string artist;
    int rank;
public:
    int get_id() const;
    string get_titlu() const;
    string get_artist() const;
    int get_rank() const;
    void set_id(int id);
    void set_titlu(string titlu);
    void set_artist(string artist);
    void set_rank(int rank);
    Melodie(int id, string titlu, string artist, int rank) : id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {} ;
};