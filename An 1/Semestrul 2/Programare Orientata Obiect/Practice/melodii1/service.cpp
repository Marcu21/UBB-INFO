#include "service.h"
#include <algorithm>
#include <vector>
#include "validator.h"

void Service::adauga(int id, string titlu, string artist, int rank) {
    Melodie melodie{ id, titlu, artist, rank };
    Validator::validate_melodie(melodie);
    repo.add(melodie);
}

void Service::sterge(int id) {
    string artist;
    for(auto m: repo.get_all())
    {
        if(m.get_id() == id) {
            artist = m.get_artist();
        }
    }
    if(artist.empty() == 1) throw std::runtime_error("Melodie inexistenta!");
    int k = -1;
    int nr = 0;
    for(auto m:repo.get_all())
    {
        if(m.get_id() == id) k = 0;
        if(m.get_artist() == artist && k == 0) nr++;
    }
    if(nr>1)
        repo.remove(id);
    else
        throw std::runtime_error("Melodia este ultima piesa a artistului!");
}

void Service::modifica(int id, string titlu, string artist, int rank) {
    Melodie melodie{ id, titlu, artist, rank };
    Validator::validate_melodie(melodie);
    repo.update(id, melodie);
}

Melodie Service::cauta(int id) {
    return repo.find(id);
}

vector<Melodie> Service::get_all() {
    return repo.get_all();
}

vector<Melodie> Service::sortare_rank() {
    vector<Melodie> melodii = repo.get_all();
    std::sort(melodii.begin(), melodii.end(), [](const Melodie& m1, const Melodie& m2) {
        return m1.get_rank() < m2.get_rank();
    });
    return melodii;
}

int Service::frecventa_rank(int rank) {
    vector<Melodie> melodii = repo.get_all();
    return std::count_if(melodii.begin(), melodii.end(), [rank](const Melodie& melodie) {
        return melodie.get_rank() == rank;
    });
}

vector<Melodie> Service::get_all_sorted_by_rank() {
    vector<Melodie> melodii = repo.get_all();
    std::sort(melodii.begin(), melodii.end(), [](const Melodie& m1, const Melodie& m2) {
        return m1.get_rank() < m2.get_rank();
    });
    return melodii;
}