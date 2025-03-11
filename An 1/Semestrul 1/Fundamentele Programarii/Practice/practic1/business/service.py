from datetime import datetime, timedelta
from domain.examen import *
from domain.validator import *
from persistenta.repository import *
repo = RepositoryExamen("examen.txt")
validator = ValidatorExamen()
class ServiceExamen:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def adaugare(self, data, ora, materia, sesiune):
        examen = Examen(data, ora, materia, sesiune)
        try:
            self.__validator.valideaza_examen(examen)
            self.__repo.adauga(examen)
        except Exception as ex:
            print(ex)

    def examene_ziua_urmatoare(self):
        azi = datetime.now().date()
        maine = azi + timedelta(days=1)
        lista_examene = self.__repo.load_from_file()
        lista = [examen for examen in lista_examene if examen.get_data() == maine.strftime('%d.%m')]
        lista = sorted(lista, key = lambda examen: examen.get_ora())
        return lista

    def examene_3_zile(self, data):
        try:
            data = datetime.strptime(data, '%d.%m')
        except ValueError:
            print("Data introdusa nu este corecta.")

        lista_examene = self.__repo.load_from_file()
        lista = [examen for examen in lista_examene if data<=datetime.strptime(examen.get_data(), '%d.%m')<=data+timedelta(days=2)]
        lista = sorted(lista, key=lambda examen:(examen.get_data(), examen.get_ora()))
        return lista

    def export_examene_fisier(self, nume_fisier, sir):
        lista_examene = self.__repo.load_from_file()
        lista_examene = [examen for examen in lista_examene if sir in examen.get_materia()]
        lista_examene = sorted(lista_examene, key=lambda examen: (examen.get_data(), examen.get_ora()))
        if len(lista_examene) == 0:
            print("Nu sunt examene care contin sirul respectiv in materie.")
        else:
            with open(nume_fisier, "w") as f:
                for examen in lista_examene:
                    f.write(str(examen))
            print("Examenele au fost exportate cu succes")