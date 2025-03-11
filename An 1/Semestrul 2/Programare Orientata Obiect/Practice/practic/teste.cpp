#include <cassert>
#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <iostream>
using std::cout;

void test_domain()
{
    //Testeaza partea de domain
    Utilaj u{1, "tractor", "bun", 2};
    assert(u.get_id() == 1);
    assert(u.get_denumire()=="tractor");
    assert(u.get_tip()=="bun");
    assert(u.get_cilindrii()==2);
    u.set_id(11);
    u.set_denumire("tractortractor");
    u.set_tip("bunbun");
    u.set_cilindrii(4);
    assert(u.get_id() == 11);
    assert(u.get_denumire()=="tractortractor");
    assert(u.get_tip()=="bunbun");
    assert(u.get_cilindrii()==4);
    cout<<"Testele pentru domain au trecut cu succes!"<<'\n';
}

void test_repo()
{
    //Testeaza partea de repo
    Repo repo;
    Utilaj u{1, "tractor", "bun", 2};
    repo.add(u);
    assert(repo.get_all().size()==1);
    assert(repo.get_all()[0].get_denumire() == "tractor");
    Utilaj um{1, "tractortr", "bun", 2};
    repo.modify(1,um);
    assert(repo.get_all()[0].get_denumire() == "tractortr");
    assert(repo.find(1).get_denumire() == "tractortr");
    repo.remove(1);
    assert(repo.get_all().size()==0);
    try
    {
        repo.remove(11);
        assert(false);
    }
    catch (std::runtime_error& e)
    {
        assert(true);
    }
    try
    {
        repo.modify(11,um);
        assert(false);
    }
    catch (std::runtime_error& e)
    {
        assert(true);
    }
    try
    {
        repo.find(13);
        assert(false);
    }
    catch (std::runtime_error& e)
    {
        assert(true);
    }
    cout<<"Testele pentru repo au trecut cu succes!"<<'\n';
}

void test_service()
{
    //Testeaza partea de service
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.adauga(1, "tractor", "bun", 2);
    service.adauga(2, "coupe", "tare", 8);
    service.adauga(3, "cls", "bomba", 6);
    service.adauga(4, "treiar", "slabut", 4);
    service.adauga(5, "septar", "okish", 8);
    service.adauga(6, "renault", "nu", 2);
    service.adauga(7, "mercedes", "tare", 8);
    service.adauga(8, "opel", "bomba", 2);
    service.adauga(9, "skoda", "merge", 2);
    service.adauga(10, "megane", "bun", 8);
    assert(service.get_all().size() == 10);
    assert(service.get_all()[9].get_denumire() == "megane");
    service.modifica(10,"insignia","smecher",8);
    assert(service.get_all()[9].get_denumire() == "insignia");
    assert(service.cauta(1).get_denumire() == "tractor");
    service.adauga(11, "nu", "bun", 8);
    assert(service.get_all().size() == 11);
    service.sterge(10);
    assert(service.get_all().size() == 10);
    assert(service.get_all_sortat().size() == 10);
    try
    {
        service.adauga(-1, "", "", 3);
        assert(false);
    }
    catch (std::runtime_error& e)
    {
        assert(true);
    }
    service.adauga(12, "fsd", "bufdn", 1);
    try
    {
        service.sterge(12);
        assert(false);
    }
    catch (std::runtime_error& e)
    {
        assert(true);
    }
    cout<<"Teste pentru service au trecut cu succes!"<<'\n';
}


void ruleaza_toate_testele()
{
    //Ruleaza toate testele
    test_domain();
    test_repo();
    test_service();
}