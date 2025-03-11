from domain.magazin import *
from domain.validator import *
from persistenta.repository import *
from business.service import *

class Teste:
    def __init__(self):
        self.__validator = Validator()
        self.__repo = RepositoryMagazin("test/test_magazin.txt")
        self.__service = ServiceMagazin(self.__repo, self.__validator)

    def teste_magazin(self):
        magazin = Magazin(2, 'kaufland', 111)
        assert magazin.get_id() == 2
        assert magazin.get_denumire() == 'kaufland'
        assert magazin.get_pret() == 111

    def teste_service(self):
        self.__service.sterge_filtru()
        self.__service.adaugare("3","edex","100")
        lista = self.__repo.load_from_file()
        assert lista[0].get_id() == "3"
        assert lista[0].get_denumire() == "edex"
        assert lista[0].get_pret() == "100"

        try:
            self.__service.adaugare("-1", "", "-11")
            assert False
        except Exception:
            assert True

        try:
            self.__service.adaugare("3", "kaufland", "11")
            assert False
        except Exception:
            assert True

        self.__service.adaugare("13", "kaufland", "100")
        lista = self.__repo.load_from_file()
        assert len(lista) == 2
        self.__service.adaugare("11", "profi", "1010")
        lista_noua = self.__service.stergere("3")
        assert lista_noua == 2
        lista = self.__repo.load_from_file()
        assert len(lista) == 1
        self.__service.adaugare("13", "kaufland", "100")
        lista = self.__service.filtered_load()
        assert len(lista) == 2
        self.__service.adaugare("20", "kaufland", "1100")
        self.__service.set_filtru("kau", "2000")
        lista = self.__service.filtered_load()
        assert len(lista) == 2
        self.__service.sterge_filtru()
        lista = self.__service.filtered_load()
        assert len(lista) == 3
        self.__service.set_filtru("profi", "-1")
        lista = self.__service.filtered_load()
        assert len(lista) == 1
        self.__service.set_filtru("profi", "1")
        lista = self.__service.filtered_load()
        assert len(lista) == 0
        self.__service.set_filtru('', "1100")
        lista = self.__service.filtered_load()
        assert len(lista) == 2
        self.__service.sterge_filtru()
        self.__service.stergere("1")
        lista = self.__service.filtered_load()
        assert len(lista) == 1
        self.__service.undo()
        lista = self.__service.filtered_load()
        assert len(lista) == 3
        




    def ruleaza_toate_testele(self):
        self.teste_magazin()
        self.teste_service()