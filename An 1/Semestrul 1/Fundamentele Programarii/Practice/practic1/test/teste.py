from domain.examen import *
from persistenta.repository import *
from business.service import *
repo = RepositoryExamen("teste_examen.txt")
validator = ValidatorExamen()
service = ServiceExamen(repo, validator)
class Teste:
    def test_domain(self):
        examen = Examen("22.04", "08:00", "FP", "normala")
        assert examen.get_data() == "22.04"
        assert examen.get_ora() == "08:00"
        assert examen.get_materia() == "FP"
        assert examen.get_sesiune() == "normala"

    def test_service(self):
        lista = []
        examen = Examen("22.04", "08:00", "FP", "normala")
        lista.append(examen)
        service.adaugare("22.04", "08:00", "FP", "normala")
        af = repo.load_from_file()
        assert len(af) > 0

        assert af[0].get_data() == examen.get_data()
        assert af[0].get_ora() == examen.get_ora()
        assert af[0].get_materia() == examen.get_materia()
        assert af[0].get_sesiune() == examen.get_sesiune()


        try:
            service.adaugare("22.13", "08:61", "", "nutzspun")
            assert False
        except Exception as ve:
            assert True

        examen1 = Examen("29.01", "10:00", "Analiza", "normala")
        examen2 = Examen("29.01", "16:00", "Algebra", "restanta")
        service.adaugare("29.01", "10:00", "Analiza", "normala")
        service.adaugare("29.01", "16:00", "Algebra", "restanta")
        af = service.examene_ziua_urmatoare()
        assert len(af) > 0

        assert af[0].get_data() == examen1.get_data()
        assert af[0].get_ora() == examen1.get_ora()
        assert af[0].get_materia() == examen1.get_materia()
        assert af[0].get_sesiune() == examen1.get_sesiune()

        assert af[1].get_data() == examen2.get_data()
        assert af[1].get_ora() == examen2.get_ora()
        assert af[1].get_materia() == examen2.get_materia()
        assert af[1].get_sesiune() == examen2.get_sesiune()

        examen3 = Examen("30.01", "16:00", "Logica", "restanta")
        service.adaugare("30.01", "16:00", "Logica", "restanta")
        data = "28.01"
        af = service.examene_3_zile(data)
        assert len(af) > 0

        assert af[0].get_data() == examen1.get_data()
        assert af[0].get_ora() == examen1.get_ora()
        assert af[0].get_materia() == examen1.get_materia()
        assert af[0].get_sesiune() == examen1.get_sesiune()

        assert af[1].get_data() == examen2.get_data()
        assert af[1].get_ora() == examen2.get_ora()
        assert af[1].get_materia() == examen2.get_materia()
        assert af[1].get_sesiune() == examen2.get_sesiune()

        assert af[2].get_data() == examen3.get_data()
        assert af[2].get_ora() == examen3.get_ora()
        assert af[2].get_materia() == examen3.get_materia()
        assert af[2].get_sesiune() == examen3.get_sesiune()

    def ruleaza_toate_testele(self):
        self.test_domain()
        self.test_service()