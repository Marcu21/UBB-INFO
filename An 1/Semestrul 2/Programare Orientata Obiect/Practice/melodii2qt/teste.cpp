#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <iostream>
using namespace std;

void test_domain()
{
    Melodie m{1, "baba", "gheboasa", "pop"};
    assert(m.get_id() == 1);
    assert(m.get_titlu() == "baba");
    assert(m.get_artist() == "gheboasa");
    assert(m.get_gen() == "pop");
    m.set_id(2);
    m.set_titlu("mama");
    m.set_artist("gheboasa");
    m.set_gen("jazz");
    assert(m.get_id() == 2);
    assert(m.get_titlu() == "mama");
    assert(m.get_artist() == "gheboasa");
    assert(m.get_gen() == "jazz");
    cout << "Testele pentru clasa Melodie au trecut cu succes!" << endl;
}

void test_repo()
{
    Repo repo{"C:\\Users\\emanu\\CLionProjects\\melodii2qt\\fisier.txt"};
    Melodie m1{1, "baba", "gheboasa", "pop"};
    repo.add(m1);
    assert(repo.get_all().size() == 1);
    Melodie m2{2, "tiganca", "tzanca", "jazz"};
    repo.add(m2);
    assert(repo.get_all().size() == 2);
    Melodie m3{3, "diamant", "mocanu", "rock"};
    repo.add(m3);
    assert(repo.get_all().size() == 3);
    assert(repo.find(2).get_titlu() == "tiganca");
    assert(repo.find(3).get_titlu() == "diamant");
    repo.destroy(2);
    assert(repo.get_all().size() == 2);
    Melodie m3nou{3, "tiganca", "tzanca", "jazz"};
    repo.modify(3,m3nou);
    assert(repo.find(3).get_titlu() == "tiganca");
    cout << "Testele pentru clasa Repo au trecut cu succes!" << endl;
}

void test_service()
{
    Repo repo{"C:\\Users\\emanu\\CLionProjects\\melodii2qt\\fisier.txt"};
    Service service{repo};
    service.adauga(1, "baba", "gheboasa", "pop");
    assert(service.get_all().size() == 1);
    try {
        service.adauga(2, "tiganca", "tzanca", "jazz");
        assert(false);
    }
    catch (std::runtime_error& e)
    {
        assert(true);
    }
    service.adauga(2, "diamant", "mocanu", "rock");
    assert(service.get_all().size() == 2);
    assert(service.cauta(2).get_titlu() == "diamant");
    service.modifica(2, "tiganca", "tzanca", "disco");
    assert(service.get_all().size() == 2);
    assert(service.cauta(2).get_titlu() == "tiganca");
    service.sterge(2);
    assert(service.get_all().size() == 1);
    service.adauga(2, "x", "alex", "rock");
    assert(service.sortare()[0].get_artist() == "alex");
    cout << "Testele pentru clasa Service au trecut cu succes!" << endl;
}

void ruleaza_toate_testele()
{
    test_domain();
    test_repo();
    test_service();
    cout << "Toate testele au trecut cu succes!" << endl;
}