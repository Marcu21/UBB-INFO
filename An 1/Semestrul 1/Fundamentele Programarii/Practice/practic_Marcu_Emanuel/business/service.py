from datetime import datetime
from domain.tractor import *
from domain.validator import *
from persistenta.repository import *
repo = RepositoryTractoare("tractoare.txt")
validator = Validator()

class ServiceTractoare:
    def __init__(self, repo, validator):
        '''
        Reprezinta service-ul de tractoare
        :param repo: RepositoryTractoare
        :param validator: Validator
        '''
        self.__repo = repo
        self.__validator = validator
        self.__filtru_denumire = ''
        self.__filtru_pret = -1
        self.__undo = []

    def adauga(self, id, denumire, pret, model, data):
        '''
        Creaaza si adauga un tractor
        raises ValueError daca tractorul nu este valid
        raises Exception daca exista deja un tractor cu acest id
        :param id: int
        :param denumire: string
        :param pret: int
        :param model: string
        :param data: string
        :return:
        '''
        tractor = Tractor(id, denumire, pret, model, data)
        self.__validator.valideaza_tractor(tractor)
        lista = self.get_all()
        self.__undo = lista
        self.__repo.adaugare(tractor)

    def sterge(self, cifra):
        '''
        Sterge tractoarele pentru care pretul contine cifra
        raises Exception daca nu exista tractoare pentru care pretul contine cifra
        :param cifra: int
        :return: numarul de tractoare sterse
        '''
        lista = self.get_all()
        self.__undo = lista
        return self.__repo.stergere(cifra)

    def get_all(self):
        '''
        Returneaza toate tractoarele
        :return: lista
        '''
        return self.__repo.get_all()

    def set_filtru_denumire(self, filtru):
        '''
        Seteaza un filtru de denumire
        :param filtru: string
        :return:
        '''
        self.__filtru_denumire = filtru

    def set_filtru_pret(self, filtru):
        '''
        Seteaza un filtru de pret
        :param filtru: int
        :return:
        '''
        self.__filtru_pret = filtru

    def get_filtru_denumire(self):
        '''
        Returneaza filtrul de denumire
        :return: string
        '''
        return self.__filtru_denumire

    def get_filtru_pret(self):
        '''
        Returneaza filtrul de pret
        :return: int
        '''
        return self.__filtru_pret

    def clear_filtru_denumire(self):
        '''
        Sterge filtrul de denumire
        :return:
        '''
        self.__filtru_denumire = ''

    def clear_filtru_pret(self):
        '''
        Sterge filtrul de pret
        :return:
        '''
        self.__filtru_pret = -1

    def filtrare(self):
        '''
        Filtreaza tractoarele dupa filtre si adauga '*' in fata descrierii daca au revizia expirata
        :return: lista
        '''
        l1 = self.get_all()
        azi = datetime.now().date()
        l = []
        for element in l1:
            element_date_strip = element.get_data().strip()
            element_date = datetime.strptime(element_date_strip, '%d.%m.%Y').date()
            if element_date < azi:
                denumire = "*" + element.get_denumire()
                element.set_denumire(denumire)
                l.append(element)
            else:
                l.append(element)
        if self.__filtru_denumire == '' and self.__filtru_pret == -1:
            return l
        elif self.__filtru_denumire != '' and self.__filtru_pret == -1:
            lista = [el for el in l if self.__filtru_denumire in el.get_denumire()]
            return lista
        elif self.__filtru_denumire == '' and self.__filtru_pret != -1:
            lista = [el for el in l if int(el.get_pret()) < int(self.__filtru_pret)]
            return lista
        else:
            lista = [el for el in l if self.__filtru_denumire in el.get_denumire() and int(el.get_pret()) < int(self.__filtru_pret)]
            return lista

    def undo(self):
        '''
        Reface ultima operatie de tip adaugare/stergere
        :return: lista initiala
        '''
        lista = self.__undo
        self.__repo.salveaza_lista(lista)
        return self.__undo

    def sterge_tot(self):
        '''
        Sterge toate tractoarele din fisier
        :return:
        '''
        self.__repo.sterge_tot()