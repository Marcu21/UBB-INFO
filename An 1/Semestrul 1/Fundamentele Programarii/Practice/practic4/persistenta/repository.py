from domain.emisiuni import *

class RepositoryEmisiuni:
    def __init__(self, filename):
        self.__filename = filename

    def load_from_file(self):
        l = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line!='':
                    nume, tip, durata, descriere = line.split(",")
                    emisiune = Emisiuni(nume,tip,durata,descriere)
                    l.append(emisiune)
        return l

    def save_to_file(self, l):
        with open(self.__filename, "w") as f:
            for emisiune in l:
                f.write(repr(emisiune)+'\n')

    def add_to_file(self, emisiune):
        l = self.load_from_file()
        for el in l:
            if emisiune.get_nume() == el.get_nume() and emisiune.get_tip() == el.get_tip():
                raise Exception("Emisiune cu acest nume exista deja!")
        l.append(emisiune)
        self.save_to_file(l)


    def delete_from_file(self, nume, tip):
        l = self.load_from_file()
        lista = [el for el in l if el.get_nume() != nume or el.get_tip() != tip]
        if len(l) == len(lista):
            raise Exception("Aceasta emisiune nu exista!")
        self.save_to_file(lista)


    def modificare(self, nume, tip, durata, descriere):
        l = self.load_from_file()
        ok = 0
        for el in l:
            if el.get_nume() == nume and el.get_tip() == tip:
                el.set_durata(durata)
                el.set_descriere(descriere)
                ok = 1
        if ok == 0:
            raise Exception("Aceasta emisiune nu exista!")
        self.save_to_file(l)

