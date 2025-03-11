from domain.tractor import *

class RepositoryTractoare:
    def __init__(self, filename):
        '''
        Reprezinta repository-ul de tractoare
        :param filename: file name
        '''
        self.__filename = filename

    def __load_from_file(self):
        '''
        Returneaza sub forma unei liste toate datele din fisier
        :return:
        '''
        lista = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    id, denumire, pret, model, data = line.split(",")
                    tractor = Tractor(id, denumire, pret, model, data)
                    lista.append(tractor)
        return lista

    def __save_to_file(self, lista):
        '''
        Salveaza lista in fisier
        :param lista: lista
        :return:
        '''
        with open(self.__filename, "w") as f:
            for tractor in lista:
                f.write(repr(tractor)+'\n')

    def adaugare(self, tractor):
        '''
        Adauga un tractor in fisier
        raises Exception daca exista deja un tractor cu acest id
        :param tractor: tractor
        :return:
        '''
        lista = self.__load_from_file()
        for element in lista:
            if element.get_id() == tractor.get_id():
                raise Exception("Exista deja un tractor cu acest id!")
        lista.append(tractor)
        self.__save_to_file(lista)
    def salveaza_lista(self, lista):
        self.__save_to_file(lista)

    def stergere(self, cifra):
        '''
        Sterge un tractor din fisier pentru care pretul contine cifra data
        :param cifra: cifra
        :return:
        '''
        lista = self.__load_from_file()
        lista_noua = [el for el in lista if str(cifra) not in str(el.get_pret())]
        if len(lista) == len(lista_noua):
            raise Exception("Nu exista tractoare pentru care pretul contine cifra data")
        self.__save_to_file(lista_noua)
        return len(lista) - len(lista_noua)

    def sterge_tot(self):
        '''
        Goleste tot fisierul
        :return:
        '''
        lista = []
        self.__save_to_file(lista)

    def get_all(self):
        lista = []
        lista = self.__load_from_file()
        return lista