#include "domain.h"

void Melodie::set_id(int id_nou) {
    this->id = id_nou;
}

void Melodie::set_titlu(std::string titlu_nou) {
    this->titlu = titlu_nou;
}

void Melodie::set_artist(std::string artist_nou) {
    this->artist = artist_nou;
}

void Melodie::set_gen(std::string gen_nou) {
    this->gen = gen_nou;
}

int Melodie::get_id() const{
    return id;
}

string Melodie::get_titlu() const{
    return titlu;
}

string Melodie::get_artist() const{
    return artist;
}

string Melodie::get_gen() const{
    return gen;
}