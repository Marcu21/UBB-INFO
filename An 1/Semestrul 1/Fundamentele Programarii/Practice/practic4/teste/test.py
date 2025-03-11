from domain.emisiuni import *
from persistenta.repository import *
from business.service import *

class Teste:
    def __init__(self):
        self.__validator = ValidatorEmisiune()
        self.__repo = RepositoryEmisiuni("teste/test_emisiuni.txt")
        self.__service = ServiceEmisiuni(self.__repo, self.__validator)
    def test_domain(self):
        emisiune = Emisiuni("furtuna pe bosfor","telenovela","2","telenovela turceasca tare")
        assert emisiune.get_nume() == "furtuna pe bosfor"
        assert emisiune.get_tip() == "telenovela"
        assert emisiune.get_durata() == "2"
        assert emisiune.get_descriere() == "telenovela turceasca tare"

    def test_service(self):
        l = self.__service.get_all()
        assert len(l) == 0
        self.__service.adauga("furtuna pe bosfor","telenovela","2","telenovela turceasca tare")
        l = self.__service.get_all()
        assert len(l) == 1
        self.__service.adauga("schimb de mame", "drama", "1", "show")
        l = self.__service.get_all()
        assert len(l) == 2
        assert l[0].get_nume() == "furtuna pe bosfor"
        assert l[0].get_tip() == "telenovela"
        assert l[0].get_durata() == "2"
        assert l[0].get_descriere() == "telenovela turceasca tare"
        assert l[1].get_nume() == "schimb de mame"
        assert l[1].get_tip() == "drama"
        assert l[1].get_durata() == "1"
        assert l[1].get_descriere() == "show"
        self.__service.modifica("schimb de mame", "drama", "3", "prostie")
        l = self.__service.get_all()
        assert len(l) == 2
        assert l[1].get_nume() == "schimb de mame"
        assert l[1].get_tip() == "drama"
        assert l[1].get_durata() == "3"
        assert l[1].get_descriere() == "prostie"
        try:
            self.__service.adauga("", "", -1, '')
            assert False
        except ValueError:
            assert True

        try:
            self.__service.adauga("schimb de mame", "drama", "2", "nush")
            assert False
        except Exception:
            assert True
        self.__service.blocheaza_tip("telenovela")
        l = self.__service.get_all()
        assert len(l) == 1
        try:
            self.__service.sterge("furtuna pe bosfor", "telenovela")
            assert False
        except Exception:
            assert True
        self.__service.sterge_blocare_tip()
        l = self.__service.get_all()
        assert len(l) == 2
        self.__service.sterge("furtuna pe bosfor", "telenovela")
        l = self.__service.get_all()
        assert len(l) == 1
        self.__service.sterge("schimb de mame", "drama")
        l = self.__service.get_all()
        assert len(l) == 0

    def ruleaza_toate_testele(self):
        self.test_domain()
        self.test_service()