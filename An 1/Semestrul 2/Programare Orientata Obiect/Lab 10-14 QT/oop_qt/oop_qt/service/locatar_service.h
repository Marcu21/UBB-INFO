#pragma once
#include <string>
#include "../domain/locatar.h"
#include "../repository/locatar_repo.h"
#include <map>
#include "../utils/undo.h"
#include <memory>
#include "../utils/observer.h"

using std::string;

class locatar_service : public Observable
{
private:
    LocatarRepository& repo;
    std::vector<int> notification_list;
    std::vector<std::unique_ptr<ActiuneUndo>> undoStack;
public:
    explicit locatar_service(LocatarRepository& repo) :repo{ repo } {

    }
    //locatar_service(const locatar_service& service) = delete;
    //locatar_service() = default;
    void add(int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament);

    std::vector<Locatar>& get_all();

    void sterge(int apartament, const string& nume_proprietar);

    void modifica(int apartament, const string& nume_proprietar, int suprafata, const string& tip_apartament);

    Locatar cauta(int apartament);

    std::vector<Locatar> filtrare_tip(const string& tip_apartament);

    std::vector<Locatar> filtrare_suprafata(int suprafata);

    std::vector<Locatar> sortare_nume_proprietar();

    std::vector<Locatar> sortare_suprafata();

    std::vector<Locatar> sortare_tip_suprafata();

    void add_notification(int apartment);

    void clear_notifications();

    [[nodiscard]] const std::vector<int>& get_notifications() const;

    void generate_notifications(int count);

    void export_to_csv(const std::string& filename) const;

    void export_to_html(const std::string& filename) const;

    std::map<std::string, int> raport_tip_apartament();

    std::vector<string> getUniqueTypes() const;

    int countByType(const string& type) const;

    void undo();
};
