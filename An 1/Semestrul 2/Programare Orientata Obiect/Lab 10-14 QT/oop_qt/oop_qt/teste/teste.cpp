#include "../service/locatar_service.h"
#include "../domain/locatar.h"
#include "../validators/exception.h"
#include "../repository/locatar_repo.h"
#include "../validators/validator.h"
#include <cassert>
#include <vector>
#include <set>


void test_locatar()
//Testeaza clasa Locatar
{
    Locatar l;
    l = Locatar::creeaza_locatar(l, 1, "Popescu", 100, "apartament");
    assert(l.get_apartament() == 1);
    assert(l.get_nume_proprietar() == "Popescu");
    assert(l.get_suprafata() == 100);
    assert(l.get_tip_apartament() == "apartament");
    printf("Testele pentru clasa Locatar au trecut cu succes!\n");
}

void test_validator()
//Testeaza clasa validator
{
    Locatar l;
    l = Locatar::creeaza_locatar(l, 1, "Popescu", 100, "apartament");
    assert(l.get_apartament() == 1);
    assert(l.get_nume_proprietar() == "Popescu");
    assert(l.get_suprafata() == 100);
    assert(l.get_tip_apartament() == "apartament");
    validator::validate_locatar(l);
    l = Locatar::creeaza_locatar(l,1, "", 100, "apartament");
    try {
        validator::validate_locatar(l);
        assert(false);
    }
    catch (validator_exception& ex) {
        assert(ex.get_msg() == "Numele proprietarului nu poate fi vid.");
    }

    l = Locatar::creeaza_locatar(l,1, "Popescu", 0, "apartament");
    try {
        validator::validate_locatar(l);
        assert(false);
    }
    catch (validator_exception& ex) {
        assert(ex.get_msg() == "Suprafata trebuie sa fie un numar pozitiv nenul.");
    }

    l = Locatar::creeaza_locatar(l,0, "Popescu", 100, "apartament");
    try {
        validator::validate_locatar(l);
        assert(false);
    }
    catch (validator_exception& ex) {
        assert(ex.get_msg() == "Numarul apartamentului trebuie sa fie un numar pozitiv nenul.");
    }

    l = Locatar::creeaza_locatar(l,1, "Popescu", 100, "");
    try {
        validator::validate_locatar(l);
        assert(false);
    }
    catch (validator_exception& ex) {
        assert(ex.get_msg() == "Tipul apartamentului nu poate fi vid.");
    }
    printf("Testele pentru clasa Validator au trecut cu succes!\n");
}

void test_repo()
//Testeaza clasa Repo
{
    locatar_repo repo;
    Locatar l;
    l = Locatar::creeaza_locatar(l, 1, "Popescu", 100, "apartament");
    repo.store(l);
    const std::vector<Locatar>& locatari = repo.get_all();
    assert(locatari.size() == 1);

    try {
        repo.store(l);
        assert(false);
    }
    catch (repo_exception& ex) {
        assert(ex.get_msg() == "Locatar deja existent!");
    }
    l = Locatar::creeaza_locatar(l,2, "Ionescu", 99, "apartament");
    repo.store(l);
    assert(locatari[1].get_nume_proprietar() == "Ionescu");
    l = Locatar::creeaza_locatar(l,3, "Georgescu", 98, "apartament");
    repo.store(l);
    assert(locatari[2].get_nume_proprietar() == "Georgescu");
    l = Locatar::creeaza_locatar(l,4, "Pop", 97, "apartament");
    repo.store(l);
    assert(locatari[3].get_nume_proprietar() == "Pop");
    l = Locatar::creeaza_locatar(l,5, "Ion", 96, "apartament");
    repo.store(l);
    assert(locatari[4].get_nume_proprietar() == "Ion");
    assert(repo.get_all().size() == 5);
    repo.destroy(1, "Popescu");
    assert(repo.get_all().size() == 4);
    try {
        repo.destroy(1, "Popescu");
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }

    repo.modify(2, "Ionescu", 100, "apartament");
    assert(repo.get_all()[0].get_suprafata() == 100);
    try {
        repo.modify(1, "Popescu", 100, "apartament");
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }

    Locatar locatar = repo.find(2);
    assert(locatar.get_nume_proprietar() == "Ionescu");
    try {
        repo.find(1);
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }
    printf("Testele pentru clasa Repo au trecut cu succes!\n");
}

void test_service()
//Testeaza clasa Service
{
    locatar_repo repo;
    locatar_service service{ repo };
    service.add(1, "nume1", 11, "apartament");
    const auto& locatari = service.get_all();
    assert(locatari.size() == 1);

    try {
        service.add(1, "nume1", 22, "apartament");
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }
    service.add(2, "nume2", 33, "apartament");
    service.add(3, "nume3", 44, "apartament");
    service.sterge(1, "nume1");
    assert(service.get_all().size() == 2);
    try {
        service.sterge(1, "nume");
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }
    service.modifica(2, "popan", 100, "apartament");
    assert(service.get_all()[0].get_suprafata() == 100);

    try {
        service.modifica(1, "nume", 100, "apartament");
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }

    Locatar locatar = service.cauta(2);
    assert(locatar.get_nume_proprietar() == "popan");
    try {
        service.cauta(1);
        assert(false);
    }
    catch (repo_exception&) {
        assert(true);
    }

    service.add(4, "nume4", 55, "apartament");

    std::vector<Locatar> locatari_filtrate = service.filtrare_suprafata(55);
    assert(locatari_filtrate.size() == 1);
    assert(locatari_filtrate[0].get_suprafata() == 55);

    std::vector<Locatar> locatari_filtrate2 = service.filtrare_suprafata(100);
    assert(locatari_filtrate2.size() == 1);
    assert(locatari_filtrate2[0].get_suprafata() == 100);

    std::vector<Locatar> locatari_filtrate3 = service.filtrare_tip("apartament");
    assert(locatari_filtrate3.size() == 3);

    std::vector<Locatar> locatari_filtrate4 = service.filtrare_tip("garsoniera");
    assert(locatari_filtrate4.empty() == 1);

    std::vector<Locatar> locatari_sortare = service.sortare_nume_proprietar();
    assert(locatari_sortare.size() == 3);
    assert(locatari_sortare[0].get_nume_proprietar() == "nume3");
    assert(locatari_sortare[1].get_nume_proprietar() == "nume4");
    assert(locatari_sortare[2].get_nume_proprietar() == "popan");
    service.add(5, "nume5", 1, "apartament");
    std::vector<Locatar> locatari_sortare2 = service.sortare_suprafata();
    assert(locatari_sortare2.size() == 4);
    assert(locatari_sortare2[0].get_suprafata() == 1);
    assert(locatari_sortare2[1].get_suprafata() == 44);
    assert(locatari_sortare2[2].get_suprafata() == 55);
    assert(locatari_sortare2[3].get_suprafata() == 100);

    service.add(6, "nume6", 67, "aaa");

    std::vector<Locatar> locatari_sortare3 = service.sortare_tip_suprafata();

    assert(locatari_sortare3.size() == 5);
    assert(locatari_sortare3[0].get_suprafata() == 67);
    assert(locatari_sortare3[1].get_suprafata() == 1);
    assert(locatari_sortare3[2].get_suprafata() == 44);
    assert(locatari_sortare3[3].get_suprafata() == 55);
    assert(locatari_sortare3[4].get_suprafata() == 100);

    std::map<std::string, int> raport = service.raport_tip_apartament();
    assert(raport["apartament"] == 4);
    assert(raport["aaa"] == 1);


    std::vector<std::string> unique_types = service.getUniqueTypes();
    assert(unique_types.size() == 2);
    assert(unique_types[0] == "aaa");
    assert(unique_types[1] == "apartament");

    assert(service.countByType("apartament") == 4);
    assert(service.countByType("aaa") == 1);

    service.export_to_csv("test.csv");
    service.export_to_html("test.html");

    printf("Testele pentru clasa Service au trecut cu succes!\n");
}

void test_notification_features()
//Testeaza notificarile
{
    locatar_repo repo;
    locatar_service service(repo);

    service.add_notification(101);
    service.add_notification(102);
    service.add_notification(103);

    const auto& notifications = service.get_notifications();
    assert(notifications.size() == 3);

    service.add_notification(101);
    assert(notifications.size() == 3);

    service.clear_notifications();
    assert(notifications.empty());

    service.generate_notifications(100);
    auto notifications2 = service.get_notifications();
    assert(notifications.size() == 100);

    std::set<int> unique_notifications(notifications2.begin(), notifications2.end());
    assert(unique_notifications.size() == notifications2.size());

    service.clear_notifications();
    service.generate_notifications(1500);
    notifications2 = service.get_notifications();
    assert(notifications2.size() == 1000);

    unique_notifications = std::set<int>(notifications2.begin(), notifications2.end());
    assert(unique_notifications.size() == notifications2.size());

    cout << "Testele pentru notificari au trecut cu succes!\n";
}

void test_undo_operations() {
    // Testează operațiile de undo
    locatar_repo repo;
    locatar_service service(repo);

    service.add(1, "Popescu", 100, "apartament");
    assert(service.get_all().size() == 1);

    service.modifica(1, "Popescu", 110, "studio");
    assert(service.get_all()[0].get_suprafata() == 110);
    assert(service.get_all()[0].get_tip_apartament() == "studio");

    service.undo();
    assert(service.get_all()[0].get_suprafata() == 100);
    assert(service.get_all()[0].get_tip_apartament() == "apartament");

    service.sterge(1, "Popescu");
    assert(service.get_all().empty());

    service.undo();
    assert(service.get_all().size() == 1);
    assert(service.get_all()[0].get_apartament() == 1);

    service.undo();
    assert(service.get_all().empty());

    try {
        service.undo();
        assert(false);
    } catch (std::runtime_error& e) {
        assert(true);
    }

    cout << "Testele pentru undo au trecut cu succes!\n";
}

void test_repo_dictionar() {
//Testeaza clasa repo_dictionar
    repo_dictionar repo_low_prob(0.0);
    Locatar locatar1;
    locatar1 = Locatar::creeaza_locatar(locatar1, 1, "Smith", 50, "apartament");

    try {
        repo_low_prob.store(locatar1);
        assert(false);
    } catch (const std::runtime_error& ex) {
        assert(true);
    }

    try {
        repo_low_prob.get_all();
        assert(false);
    } catch (const std::runtime_error& ex) {
        assert(true);
    }

    repo_dictionar repo_high_prob(1.0);
    repo_high_prob.store(locatar1);
    assert(repo_high_prob.get_all().size() == 1);
    assert(repo_high_prob.find(1).get_nume_proprietar() == "Smith");

    try {
        repo_high_prob.store(locatar1);
        assert(false);
    } catch (const std::runtime_error& ex) {
        assert(true);
    }

    repo_high_prob.modify(1, "Smith", 55, "studio");
    assert(repo_high_prob.find(1).get_suprafata() == 55);
    assert(repo_high_prob.find(1).get_tip_apartament() == "studio");

    repo_high_prob.destroy(1, "Smith");
    try {
        repo_high_prob.find(1);
        assert(false);
    } catch (const std::runtime_error& ex) {
        assert(true);
    }

    std::cout << "Testele pentru repo_dictionar au trecut cu succes!" << std::endl;
}


void ruleaza_toate_testele()
//Ruleaza toate testele
{
    test_locatar();
    test_validator();
    test_repo();
    test_service();
    test_notification_features();
    test_undo_operations();
    test_repo_dictionar();
}