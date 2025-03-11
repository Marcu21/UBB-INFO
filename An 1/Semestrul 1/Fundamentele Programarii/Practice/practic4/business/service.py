from domain.emisiuni import *
from domain.validator import *
from persistenta.repository import *
repo = RepositoryEmisiuni("emisiuni.txt")
validator = ValidatorEmisiune()
import random
class ServiceEmisiuni:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator
        self.__tip = ''

    def adauga(self, nume, tip, durata, descriere):
        emisiune = Emisiuni(nume,tip,durata,descriere)
        self.__validator.valideaza_emisiune(emisiune)
        self.__repo.add_to_file(emisiune)

    def modifica(self, nume, tip, durata, descriere):
        emisiune = Emisiuni(nume, tip, durata, descriere)
        self.__validator.valideaza_emisiune(emisiune)
        if tip == self.__tip:
            raise Exception("Emisiune blocata!")
        self.__repo.modificare(nume,tip,durata,descriere)


    def get_all(self):
        l = self.__repo.load_from_file()
        lista = [emisiune for emisiune in l if emisiune.get_tip() != self.__tip]
        return lista

    def sterge(self, nume, tip):
        if tip == self.__tip:
            raise Exception("Emisiune blocata!")
        self.__repo.delete_from_file(nume, tip)


    def blocheaza_tip(self, tip):
        self.__tip = tip

    def sterge_blocare_tip(self):
        self.__tip = ''

    def tip_blocat(self):
        return self.__tip

    def durata_minima(self,l):
        timp = 10000
        for el in l:
            if int(el.get_durata()) < int(timp):
                timp = int(el.get_durata())
        return int(timp)


    def program_aleator(self, ora_inceput, ora_sfarsit):
        durata_totala = int(ora_sfarsit) - int(ora_inceput)
        durata = 0
        program = []
        l = self.get_all()
        while durata<durata_totala:
            if self.durata_minima(l) <= durata_totala - durata:
                 choice = random.randint(0, len(l)-1)
                 if int(l[choice].get_durata()) <= durata_totala - durata:
                     durata += int(l[choice].get_durata())
                     if l[choice] not in program:
                            program.append(l[choice])
                     else:
                            l[choice].set_descriere("****")
                            program.append(l[choice])
                     lista = []
                     for i in range(0,len(l)-1):
                         if i != choice:
                             lista.append(l[i])
                     l = lista
            else:
                if durata_totala - durata >= self.durata_minima(self.get_all()):
                    l = self.get_all()
                else:
                    break
        return program
