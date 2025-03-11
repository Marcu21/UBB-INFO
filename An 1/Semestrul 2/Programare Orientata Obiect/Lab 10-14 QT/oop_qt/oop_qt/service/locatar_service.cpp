#include <vector>
#include "locatar_service.h"
#include "../domain/locatar.h"
#include "../validators/validator.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <map>

void locatar_service::add(int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament){
    //Adauga un locatar daca este valid
    Locatar locatar;
    locatar = Locatar::creeaza_locatar(locatar, apartament, nume_proprietar, suprafata, tip_apartament);
    validator::validate_locatar(locatar);

    repo.store(locatar);
    undoStack.emplace_back(std::make_unique<UndoAdauga>(repo, locatar));
}

std::vector<Locatar>& locatar_service::get_all() {
    //Returneaza toti locatarii
    return repo.get_all();
}


void locatar_service::sterge(int apartament, const string& nume_proprietar){
    //Sterge un locatar
    Locatar locatar = repo.find(apartament);
    repo.destroy(apartament, nume_proprietar);
    undoStack.emplace_back(std::make_unique<UndoSterge>(repo, locatar));
}

void locatar_service::modifica(int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament){
    //Modifica un locatar daca este valid
    Locatar oldLocatar = repo.find(apartament);
    Locatar locatar;
    locatar = Locatar::creeaza_locatar(locatar, apartament, nume_proprietar, suprafata, tip_apartament);
    validator::validate_locatar(locatar);
    repo.modify(apartament, nume_proprietar, suprafata, tip_apartament);
    undoStack.emplace_back(std::make_unique<UndoModifica>(repo, oldLocatar, locatar));
}

Locatar locatar_service::cauta(int apartament){
    //Cauta un locatar
    return repo.find(apartament);
}


std::vector<Locatar> locatar_service::filtrare_tip(const string& tip_apartament) {
    //Filtreaza locatarii dupa tipul apartamentului
    std::vector<Locatar>& locatari = repo.get_all();
    std::vector<Locatar> locatari_filtrate;

    std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(locatari_filtrate),
                 [&tip_apartament](const Locatar& locatar) {
                     return locatar.get_tip_apartament() == tip_apartament;
                 });

    return locatari_filtrate;}

std::vector<Locatar> locatar_service::filtrare_suprafata(int suprafata) {
    //Filtreaza locatarii dupa suprafata
    const std::vector<Locatar>& locatari = repo.get_all();
    std::vector<Locatar> locatari_filtrate;

    std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(locatari_filtrate),
                 [suprafata](const Locatar& locatar) {
                     return locatar.get_suprafata() == suprafata;
                 });

    return locatari_filtrate;}

std::vector<Locatar> locatar_service::sortare_nume_proprietar(){
    //Sorteaza locatarii dupa numele proprietarului
    std::vector<Locatar>& locatari = repo.get_all();

    std::sort(locatari.begin(), locatari.end(), [](const Locatar& a, const Locatar& b) {
        return a.get_nume_proprietar() < b.get_nume_proprietar();
    });

    return locatari;
}


std::vector<Locatar> locatar_service::sortare_suprafata(){
    //Sorteaza locatarii dupa suprafata
    std::vector<Locatar>& locatari = repo.get_all();

    std::sort(locatari.begin(), locatari.end(),
              [](const Locatar& a, const Locatar& b) {
                  return a.get_suprafata() < b.get_suprafata();
              });

    return locatari;
}

std::vector<Locatar> locatar_service::sortare_tip_suprafata(){
    //Sorteaza locatarii dupa tipul apartamentului si suprafata
    std::vector<Locatar>& locatari = repo.get_all();

    std::sort(locatari.begin(), locatari.end(),
              [](const Locatar& a, const Locatar& b) {
                  if (a.get_tip_apartament() == b.get_tip_apartament()) {
                      return a.get_suprafata() < b.get_suprafata();
                  }
                  return a.get_tip_apartament() < b.get_tip_apartament();
              });

    return locatari;
}

void locatar_service::add_notification(int apartment) {
    //Adauga un apartament in lista de notificari
    auto it = std::find(notification_list.begin(), notification_list.end(), apartment);
    if (it == notification_list.end()) {
        notification_list.push_back(apartment);
    }
    notify();
}

void locatar_service::clear_notifications() {
    //Sterge toate notificarile
    notification_list.clear();
    notify();
}

const std::vector<int>& locatar_service::get_notifications() const {
    //Returneaza lista de notificari
    return notification_list;
}

void locatar_service::generate_notifications(int count) {
    //Genereaza notificari
    std::vector<int> apartments;
    for (int i = 1; i <= 1000; ++i) {
        apartments.push_back(i);
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(apartments.begin(), apartments.end(), mt);

    std::size_t added = 0;
    for (std::size_t i = 0; i < apartments.size() && added < static_cast<std::size_t>(count); ++i) {
        if (std::find(notification_list.begin(), notification_list.end(), apartments[i]) == notification_list.end()) {
            add_notification(apartments[i]);
            added++;
        }
    }
    notify();
}

void locatar_service::export_to_csv(const string& filename) const
{
    //Exporta notificarile in fisier CSV
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului.");
    const auto& notifications = get_notifications();
    for (int apt : notifications) file << apt << ",";
    file.close();
}

void locatar_service::export_to_html(const string& filename) const {
    //Exporta notificarile in fisier HTML
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Eroare la deschiderea fisierului.");
    const auto& notifications = get_notifications();
    file << "<html><body><h1>Notification List</h1><ul>";
    for (int apt : notifications) file << "<li>Apartment " << apt << "</li>";
    file << "</ul></body></html>";
    file.close();
}



std::map<std::string, int> locatar_service::raport_tip_apartament() {
    //Genereaza un raport pentru tipul de apartamente
    std::map<std::string, int> raport;
    const std::vector<Locatar>& locatari = repo.get_all();

    for (const auto& locatar : locatari) {
        raport[locatar.get_tip_apartament()]++;
    }

    return raport;}


void locatar_service::undo() {
    //Face operatia de undo
    if (!undoStack.empty()) {
        undoStack.back()->doUndo();
        undoStack.pop_back();
    } else {
        throw std::runtime_error("Nu exista operatii de undo!");
    }
}

std::vector<string> locatar_service::getUniqueTypes() const {
    //Returneaza toate tipurile de apartamente
    std::vector<string> types;
    for (const auto& locatar : repo.get_all()) {
        if (std::find(types.begin(), types.end(), locatar.get_tip_apartament()) == types.end()) {
            types.push_back(locatar.get_tip_apartament());
        }
    }
    return types;}

int locatar_service::countByType(const string& type) const {
    //Numara apartamentele de un anumit tip
    int count = 0;
    for (const auto& locatar : repo.get_all()) {
        if (locatar.get_tip_apartament() == type) {
            count++;
        }
    }
    return count;
}