from domain.magazin import *

class RepositoryMagazin:
    def __init__(self, filename):
        self.__filename = filename
        self.__magazine = self.load_from_file

    def load_from_file(self):
        lista = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    id, denumire, pret = line.split(",")
                    magazin = Magazin(id, denumire, pret)
                    lista.append(magazin)
        return lista

    def write_to_file(self, lista):
        with open(self.__filename, "w") as f:
            for el in lista:
                f.write(str(el))

    def adauga(self, magazin):
        lista = self.load_from_file()
        ok = 1
        for el in lista:
            if magazin.get_id() == el.get_id():
                ok = 0
                raise Exception("Produs cu acest id existent")
        if ok == 1:
            lista.append(magazin)
            self.write_to_file(lista)

    def sterge(self, cifra):
        lista = self.load_from_file()
        lista_noua = [magazin for magazin in lista if cifra not in magazin.get_id()]
        self.write_to_file(lista_noua)
        return len(lista) - len(lista_noua)


