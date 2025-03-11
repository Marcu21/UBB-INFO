from domain.tractor import *
from domain.validator import *
from persistenta.repository import *
from business.service import *
class Teste:
    def __init__(self):
        self.__repo = RepositoryTractoare("teste/test_tractoare.txt")
        self.__validator = Validator()
        self.__service = ServiceTractoare(self.__repo, self.__validator)

    def test_domain(self):
        '''
        Testeaza partea de domain
        :return:
        '''
        tractor = Tractor(1,"racheta",300,"smecherie","20.02.2023")
        assert tractor.get_id() == 1
        assert tractor.get_denumire() == "racheta"
        assert tractor.get_pret() == 300
        assert tractor.get_model() == "smecherie"
        assert tractor.get_data() == "20.02.2023"
        try:
            tractor = Tractor(-1, '', -200, '', '')
            validator.valideaza_tractor(tractor)
            assert False
        except ValueError:
            assert True

    def teste_repository(self):
        '''
        Testeaza partea de repository
        :return:
        '''
        tractor = Tractor(1, "racheta", 300, "smecherie", "20.02.2023")
        self.__repo.adaugare(tractor)
        l = self.__repo.get_all()
        assert len(l) == 1
        tractor = Tractor(2, "supertractor", 600, "barosaneala", "22.04.2023")
        self.__repo.adaugare(tractor)
        l = self.__repo.get_all()
        assert len(l) == 2
        assert l[0].get_id() == 1
        assert l[0].get_denumire() == "racheta"
        assert l[0].get_pret() == 300
        assert l[0].get_model() == "smecherie"
        assert l[0].get_data() == "20.02.2023"
        assert l[1].get_id() == 2
        assert l[1].get_denumire() == "supertractor"
        assert l[1].get_pret() == 600
        assert l[1].get_model() == "barosaneala"
        assert l[1].get_data() == "22.04.2023"

        self.__repo.stergere(3)
        l = self.__repo.get_all()
        assert len(l) == 1

        lista = []
        self.__repo.salveaza_lista(lista)
        l = self.__repo.get_all()
        assert len(l) == 0

    def teste_service(self):
        '''
        Testeaza partea de service
        :return:
        '''
        self.__service.adauga(1,"racheta",300,"smecherie","20.02.2023")
        l = self.__service.get_all()
        assert len(l) == 1
        self.__service.adauga(2, "supertractor", 600, "barosaneala", "22.04.2023")
        l = self.__service.get_all()
        assert len(l) == 2
        assert l[0].get_id() == 1
        assert l[0].get_denumire() == "racheta"
        assert l[0].get_pret() == 300
        assert l[0].get_model() == "smecherie"
        assert l[0].get_data() == "20.02.2023"
        assert l[1].get_id() == 2
        assert l[1].get_denumire() == "supertractor"
        assert l[1].get_pret() == 600
        assert l[1].get_model() == "barosaneala"
        assert l[1].get_data() == "22.04.2023"

        try:
            self.__service.adauga(-1, '', -200, '', '')
            assert False
        except ValueError:
            assert True

        l = self.__service.get_all()
        assert len(l) == 2

        self.__service.sterge(3)
        l = self.__service.get_all()
        assert len(l) == 1

        try:
            self.__service.adauga(2,"racheta",300,"smecherie","32.02.2024")
            assert False
        except Exception:
            assert True

        x = self.__service.sterge(0)
        l = self.__service.get_all()
        assert x == 1
        assert len(l) == 0

        self.__service.adauga(1, "racheta", 300, "smecherie", "20.02.2023")
        l = self.__service.get_all()
        assert len(l) == 1
        self.__service.adauga(2, "supertractor", 600, "barosaneala", "22.04.2023")
        l = self.__service.get_all()
        assert len(l) == 2
        self.__service.adauga(3, "tractor", 700, "smecherie", "21.02.2023")
        l = self.__service.get_all()
        assert len(l) == 3
        self.__service.adauga(4, "superracheta", 1000, "barosaneala", "26.04.2023")
        l = self.__service.get_all()
        assert len(l) == 4
        self.__service.set_filtru_denumire("racheta")
        lista = self.__service.filtrare()
        assert len(lista) == 2
        self.__service.set_filtru_pret(800)
        lista = self.__service.filtrare()
        assert len(lista) == 1
        self.__service.clear_filtru_denumire()
        lista = self.__service.filtrare()
        assert len(lista) == 3
        self.__service.clear_filtru_denumire()
        self.__service.clear_filtru_pret()
        lista = self.__service.filtrare()
        assert len(lista) == 4

        l = self.__service.get_all()
        x = self.__service.sterge(7)
        assert x == 1
        lista = self.__service.get_all()
        assert len(lista) == 3
        lista1 = self.__service.undo()
        assert len(lista1) == len(l)

        l = self.__service.get_all()
        assert len(l) == 4
        self.__service.adauga(5, "john deere", 1200, "tare rau", "28.04.2023")
        lista = self.__service.get_all()
        assert len(lista) == 5
        lista2 = self.__service.undo()
        assert len(lista2) == len(l)
        self.__service.sterge_tot()


    def ruleaza_toate_testele(self):
        self.test_domain()
        self.teste_repository()
        self.teste_service()