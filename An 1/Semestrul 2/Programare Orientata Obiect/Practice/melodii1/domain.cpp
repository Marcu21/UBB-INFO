#include "domain.h"
#include <string>
using std::string;

int Melodie::get_id() const {
    return id;
}

string Melodie::get_titlu() const {
    return titlu;
}

string Melodie::get_artist() const {
    return artist;
}

int Melodie::get_rank() const {
    return rank;
}

void Melodie::set_id(int id_nou) {
    this->id = id_nou;
}

void Melodie::set_titlu(string titlu_nou) {
    this->titlu = titlu_nou;
}

void Melodie::set_artist(string artist_nou) {
    this->artist = artist_nou;
}

void Melodie::set_rank(int rank_nou) {
    this->rank = rank_nou;
}