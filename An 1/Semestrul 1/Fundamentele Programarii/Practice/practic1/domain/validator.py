from datetime import datetime
from domain.examen import *
class ValidatorExamen:
    def valideaza_examen(self, examen):
        erori = ""
        data = examen.get_data()
        try:
            datetime.strptime(data, '%d.%m')
        except ValueError:
            erori += "Data invalida!\n"

        ora = examen.get_ora()
        try:
            datetime.strptime(ora, '%H:%M')
        except ValueError:
            erori += "Ora invalida!\n"

        if examen.get_materia() == "":
            erori += "Materie invalida!\n"

        if examen.get_sesiune() not in ['normala','restanta']:
            erori += "Sesiune invalida!\n"

        if len(erori)>0:
            raise Exception(erori)