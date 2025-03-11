#include "teste.h"
#include <cassert>
#include "domain.h"
#include "repo.h"

void teste_domain()
//Testeaza domain
{
    Produs prod{1, "caiet", 30, 20};
    assert(prod.get_cod()==1);
    assert(prod.get_denumire()=="caiet");
    assert(prod.get_numar()==30);
    assert(prod.get_pret()==20);
    prod.set_cod(2);
    prod.set_denumire("carte");
    prod.set_numar(11);
    prod.set_pret(3);
    assert(prod.get_cod()==2);
    assert(prod.get_denumire()=="carte");
    assert(prod.get_numar()==11);
    assert(prod.get_pret()==3);
    printf("Testele pentru domain au trecut cu succes!");
}

void teste_repo()
//Testeaza repo
{
    Repo repo;
    Produs prod12{1, "caiet", 30, 20};
    repo.add(prod12);
    vector<Produs> lista = repo.get_all();
    assert(lista.size() == 12);
    assert(lista[0].get_cod()==1);
    assert(lista[0].get_denumire()=="caiet");
    assert(lista[0].get_numar()==30);
    assert(lista[0].get_pret()==20);
}


void ruleaza_toate_testele()
{
    //Ruleaza toate testele
    teste_domain();
}