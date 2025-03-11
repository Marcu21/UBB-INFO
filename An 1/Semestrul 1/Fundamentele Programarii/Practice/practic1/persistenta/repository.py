from domain.examen import *
class RepositoryExamen:
    def __init__(self, filename):
        self.__filename = filename
        self.__examene = self.load_from_file()

    def load_from_file(self):
        lista = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                if line != '':
                    line = line.strip()
                    data, ora, materia, sesiune = line.split(",")
                    examen = Examen(data, ora, materia, sesiune)
                    lista.append(examen)
        return lista


    def save_to_file(self, lista):
        with open(self.__filename, "w") as f:
            for el in lista:
                f.write(str(el))

    def adauga(self, examen):
        lista = self.__examene
        ok = 1
        for el in lista:
            if el.get_materia() == examen.get_materia() and el.get_sesiune() == examen.get_sesiune():
                ok = 0
                raise ValueError("Nu pot exista 2 examene de acelasi fel la aceeasi materie.")
        if ok == 1:
            lista.append(examen)
            self.save_to_file(lista)