from domain.magazin import *
from domain.validator import *
from persistenta.repository import *
import random

class ServiceMagazin:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator
        self.__filtru_denumire = ''
        self.__filtru_pret = -1
        self.__undo = []

    def adaugare(self, id, denumire, pret):
        magazin = Magazin(id, denumire, pret)
        self.__validator.valideaza_magazin(magazin)
        self.__repo.adauga(magazin)

    def stergere(self, cifra):
        lista = self.__repo.load_from_file()
        self.__undo = lista
        return self.__repo.sterge(cifra)

    def undo(self):
        lista = self.__undo
        self.__repo.write_to_file(lista)

    def set_filtru(self, filtru_denumire, filtru_pret):
        self.__filtru_denumire = filtru_denumire
        self.__filtru_pret = filtru_pret

    def sterge_filtru(self):
        self.__filtru_denumire = ''
        self.__filtru_pret = "-1"

    def filtered_load(self):
        lista = self.__repo.load_from_file()
        if self.__filtru_denumire == '' and self.__filtru_pret == "-1":
            return lista
        elif self.__filtru_denumire != '' and self.__filtru_pret == "-1":
            lista_noua = [magazin for magazin in lista if self.__filtru_denumire in magazin.get_denumire()]
            return lista_noua
        elif self.__filtru_denumire == '' and self.__filtru_pret != "-1":
            lista_noua = [magazin for magazin in lista if int(magazin.get_pret())<int(self.__filtru_pret)]
            return lista_noua
        else:
            lista_noua = [magazin for magazin in lista if self.__filtru_denumire in magazin.get_denumire() and int(magazin.get_pret())<int(self.__filtru_pret)]
            return lista_noua

