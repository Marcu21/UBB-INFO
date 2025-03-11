#include "teste.h"
#include <cassert>
#include <iostream>
#include "domain.h"
#include "repo.h"
#include "service.h"

void test_domain()
{
    Melodie melodie{ 1, "titlu", "artist", 10 };
    assert(melodie.get_id() == 1);
    assert(melodie.get_titlu() == "titlu");
    assert(melodie.get_artist() == "artist");
    assert(melodie.get_rank() == 10);
    melodie.set_id(2);
    melodie.set_titlu("titlu2");
    melodie.set_artist("artist2");
    melodie.set_rank(9);
    assert(melodie.get_id() == 2);
    assert(melodie.get_titlu() == "titlu2");
    assert(melodie.get_artist() == "artist2");
    assert(melodie.get_rank() == 9);
    std::cout << "Teste domain finalizate!" << std::endl;
}

void test_repo()
{
    Repo repo;
    Melodie melodie{ 1, "titlu", "artist", 10 };
    repo.add(melodie);
    assert(repo.get_all().size() == 1);
    assert(repo.get_all()[0].get_id() == 1);
    assert(repo.get_all()[0].get_titlu() == "titlu");
    assert(repo.get_all()[0].get_artist() == "artist");
    assert(repo.get_all()[0].get_rank() == 10);
    repo.remove(1);
    assert(repo.get_all().size() == 0);
    repo.add(melodie);
    Melodie melodie2{ 2, "titlu2", "artist2", 9 };
    repo.update(1, melodie2);
    assert(repo.get_all().size() == 1);
    assert(repo.get_all()[0].get_id() == 1);
    assert(repo.get_all()[0].get_titlu() == "titlu2");
    assert(repo.get_all()[0].get_artist() == "artist2");
    assert(repo.get_all()[0].get_rank() == 9);
    assert(repo.find(1).get_id() == 1);
    assert(repo.find(1).get_titlu() == "titlu2");
    assert(repo.find(1).get_artist() == "artist2");
    assert(repo.find(1).get_rank() == 9);
    //repo.remove(1);
    std::cout << "Teste repo finalizate!" << std::endl;
}

void test_service()
{
    Repo repo;
    Service service{ repo };
    service.adauga(1, "titlu", "artist", 10);
    assert(service.get_all().size() == 1);
    assert(service.get_all()[0].get_id() == 1);
    assert(service.get_all()[0].get_titlu() == "titlu");
    assert(service.get_all()[0].get_artist() == "artist");
    assert(service.get_all()[0].get_rank() == 10);
    service.sterge(1);
    assert(service.get_all().size() == 0);
    service.adauga(1, "titlu", "artist", 10);
    service.modifica(1, "titlu2", "artist2", 9);
    assert(service.get_all().size() == 1);
    assert(service.get_all()[0].get_id() == 1);
    assert(service.get_all()[0].get_titlu() == "titlu2");
    assert(service.get_all()[0].get_artist() == "artist2");
    assert(service.get_all()[0].get_rank() == 9);
    assert(service.cauta(1).get_id() == 1);

}

void ruleaza_toate_testele()
{
    test_domain();
    test_repo();
    std::cout << "Toate testele trecute cu succes!" << std::endl;
}