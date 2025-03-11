#include "repo.h"
#include <vector>
#include <algorithm>
#include <fstream>

using std::vector;

void Repo::citeste_fisier() {
    melodii.clear();
    std::ifstream f{ fisier };
    int id, rank;
    string titlu, artist;
    while (f >> id >> titlu >> artist >> rank) {
        melodii.push_back(Melodie{ id, titlu, artist, rank });
    }
    f.close();
}

void Repo::scrie_fisier() {
    std::ofstream f{ fisier };
    for (Melodie melodie : melodii) {
        f << melodie.get_id() << " " << melodie.get_titlu() << " " << melodie.get_artist() << " " << melodie.get_rank() << "\n";
    }
    f.close();
}

void Repo::add(const Melodie& melodie) {
    for (Melodie& m : melodii)
        if (m.get_id() == melodie.get_id())
            throw std::runtime_error("Melodie deja existenta!");
    melodii.push_back(melodie);
    scrie_fisier();
}

void Repo::remove(int id) {
    auto it = std::find_if(melodii.begin(), melodii.end(), [id](const Melodie& melodie) {
        return melodie.get_id() == id;
    });

    if (it != melodii.end()) {
        melodii.erase(it);
        scrie_fisier();
    } else {
        throw std::runtime_error("Melodie inexistenta!");
    }
}

void Repo::update(int id, const Melodie& melodie) {
    for (Melodie& m : melodii) {
        if (m.get_id() == id) {
            m.set_titlu(melodie.get_titlu());
            m.set_artist(melodie.get_artist());
            m.set_rank(melodie.get_rank());
            scrie_fisier();
            return;
        }
    }
    throw std::runtime_error("Melodie inexistenta!");
}

Melodie Repo::find(int id) {
    auto it = std::find_if(melodii.begin(), melodii.end(), [id](const Melodie& melodie) {
        return melodie.get_id() == id;
    });

    if (it != melodii.end()) {
        return *it;
    } else {
        throw std::runtime_error("Melodie inexistenta!");
    }
}

vector<Melodie> Repo::get_all() {
    citeste_fisier();
    return melodii;
}