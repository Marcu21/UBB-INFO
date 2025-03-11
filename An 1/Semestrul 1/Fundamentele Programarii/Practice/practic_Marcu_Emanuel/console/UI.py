from domain.tractor import *
from domain.validator import *
from persistenta.repository import *
from business.service import *

class UI:
    def __init__(self, repo, validator, service):
        self.__repo = repo
        self.__validator = validator
        self.__service = service
    def run_ui(self):
        '''
        Reprezinta interfata utilizatorului
        :return:
        '''
        while True:
            print("1. Adaugare")
            print("2. Stergere")
            print("3. Filtrare")
            print("4. Undo")
            print("5. Exit")
            if self.__service.get_filtru_denumire() == '' and self.__service.get_filtru_pret() == -1:
                print("Nu este niciun filtru aplicat")
            elif self.__service.get_filtru_denumire() == '' and self.__service.get_filtru_pret() != -1:
                print("Filtrare dupa pret: ", self.__service.get_filtru_pret())
            elif self.__service.get_filtru_denumire() != '' and self.__service.get_filtru_pret() == -1:
                print("Filtrare dupa denumire: ", self.__service.get_filtru_denumire())
            else:
                print("Filtrare dupa denumire si pret: ", self.__service.get_filtru_denumire(), self.__service.get_filtru_pret())

            lista = self.__service.filtrare()
            l = sorted(lista, key=lambda x: x.get_id())
            for tractor in l:
                print(str(tractor))

            choice = input("Alege optiunea ta: ")
            if choice == "1":
                id = input("Introdu id: ")
                denumire = input("Introdu denumire: ")
                pret = input("Introdu pret: ")
                model = input("Introdu model: ")
                data = input("Introdu data: ")
                try:
                    self.__service.adauga(id, denumire, pret, model, data)
                except ValueError as ve:
                    print(ve)
                except Exception as ex:
                    print(ex)

            elif choice == "2":
                cifra = input("Introdu cifra: ")
                try:
                    nr = self.__service.sterge(cifra)
                    print("Numarul tractoarelor sterse: ", nr)
                except Exception as ex:
                    print(ex)

            elif choice == "3":
                print("1. Seteaza filtru pret")
                print("2. Seteaza filtru denumire")
                print("3. Sterge filtre")
                optiune = input("Alege optiunea ta: ")
                if optiune == "1":
                    filtru = input("Introdu filtrul de pret: ")
                    self.__service.set_filtru_pret(int(filtru))
                elif optiune == "2":
                    filtru = input("Introdu filtrul de denumire: ")
                    self.__service.set_filtru_denumire(filtru)
                elif optiune == "3":
                    self.__service.clear_filtru_pret()
                    self.__service.clear_filtru_denumire()
                else:
                    continue

            elif choice == "4":
                self.__service.undo()

            else:
                break


