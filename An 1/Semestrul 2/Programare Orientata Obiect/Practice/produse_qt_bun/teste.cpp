#include "teste.h"
#include "repo.h"
#include <cassert>
#include "validator.h"
#include "service.h"
#include <iostream>
void test_domain()
{
    Produs prod(1, "paine", "brutarie", 3.8);
    assert(prod.get_id() == 1);
    assert(prod.get_nume() == "paine");
    assert(prod.get_tip() == "brutarie");
    assert(prod.get_pret() == 3.8);
    prod.set_id(2);
    prod.set_nume("lapte");
    prod.set_tip("nush");
    prod.set_pret(4.7);
    assert(prod.get_id() == 2);
    assert(prod.get_nume() == "lapte");
    assert(prod.get_tip() == "nush");
    assert(prod.get_pret() == 4.7);
    printf("Testele pentru domain au trecut cu succes!\n");
}

void test_repo()
{
    Repo repo;
    Produs prod1(1, "nume1", "tip1", 1.1);
    Produs prod2(2, "nume2", "tip2", 2.2);
    repo.add(prod1);
    std::vector<Produs> lista;
    lista = repo.get_all();
    for(auto& produs: lista)
    {
        std::cout << produs.get_id() << " " << produs.get_nume() << " " << produs.get_tip() << " " << produs.get_pret() << '\n';
    }
    assert(lista.size() == 1);
    assert(lista[0].get_id() == 1);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    repo.add(prod2);
    lista = repo.get_all();
    assert(lista.size() == 2);
    assert(lista[0].get_id() == 1);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    assert(lista[1].get_id() == 2);
    assert(lista[1].get_nume() == "nume2");
    assert(lista[1].get_tip() == "tip2");
    assert(lista[1].get_pret() == 2.2);
    repo.remove(1);
    lista = repo.get_all();
    assert(lista.size() == 1);
    assert(lista[0].get_id() == 2);
    assert(lista[0].get_nume() == "nume2");
    assert(lista[0].get_tip() == "tip2");
    assert(lista[0].get_pret() == 2.2);
    repo.update(2, prod1);
    lista = repo.get_all();
    assert(lista.size() == 1);
    assert(lista[0].get_id() == 1);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    try
    {
        repo.add(prod1);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    try
    {
        repo.remove(3);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    try
    {
        repo.update(3, prod1);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    repo.remove(1);
    printf("Testele pentru repo au trecut cu succes!\n");

}

void test_service()
{
    Repo repo;
    Validator validator;
    Service service(repo, validator);
    service.adauga(1, "nume1", "tip1", 1.1);
    std::vector<Produs> lista = service.get_all();
    assert(lista.size() == 1);
    assert(lista[0].get_id() == 1);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    service.adauga(2, "nume2", "tip2", 2.2);
    lista = service.get_all();
    assert(lista.size() == 2);
    assert(lista[0].get_id() == 1);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    assert(lista[1].get_id() == 2);
    assert(lista[1].get_nume() == "nume2");
    assert(lista[1].get_tip() == "tip2");
    assert(lista[1].get_pret() == 2.2);
    service.sterge(1);
    lista = service.get_all();
    assert(lista.size() == 1);
    assert(lista[0].get_id() == 2);
    assert(lista[0].get_nume() == "nume2");
    assert(lista[0].get_tip() == "tip2");
    assert(lista[0].get_pret() == 2.2);
    service.modifica(2, "nume1", "tip1", 1.1);
    lista = service.get_all();
    assert(lista.size() == 1);
    assert(lista[0].get_id() == 2);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    service.adauga(1, "nume2", "tip2", 2.2);
    lista = service.get_all();
    assert(lista.size() == 2);
    assert(lista[0].get_id() == 2);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    assert(lista[1].get_id() == 1);
    assert(lista[1].get_nume() == "nume2");
    assert(lista[1].get_tip() == "tip2");
    assert(lista[1].get_pret() == 2.2);
    assert(service.get_numar_vocale("aeiou") == 5);
    assert(service.get_numar_vocale("bcdfghjklmnpqrstvwxyz") == 0);
    assert(service.get_numar_vocale("a") == 1);
    assert(service.get_numar_vocale("nece") == 2);
    try
    {
        service.adauga(1, "nume1", "tip1", 1.1);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    try
    {
        service.adauga(-1, "", "", -1.1);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    try
    {
        service.sterge(3);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    try
    {
        service.modifica(3, "nume1", "tip1", 1.1);
        assert(false);
    }
    catch (std::runtime_error&)
    {
        assert(true);
    }
    lista = service.sortare();
    assert(lista.size() == 2);
    assert(lista[0].get_id() == 2);
    assert(lista[0].get_nume() == "nume1");
    assert(lista[0].get_tip() == "tip1");
    assert(lista[0].get_pret() == 1.1);
    assert(lista[1].get_id() == 1);
    assert(lista[1].get_nume() == "nume2");
    assert(lista[1].get_tip() == "tip2");
    assert(lista[1].get_pret() == 2.2);
    service.sterge(1);
    //service.sterge(2);
    printf("Testele pentru service au trecut cu succes!");
}

void ruleaza_toate_testele()
{
    test_domain();
    test_repo();
    test_service();
}