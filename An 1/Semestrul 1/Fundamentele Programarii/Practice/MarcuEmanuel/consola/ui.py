from domain.pacient import Pacient
from domain.internare import Internare
from persistenta.RepositoryInternari import *
from persistenta.RepositoryPacienti import *
from business.service import ServicePacienti


repo_internari = RepoInternari()
file_repo_internari = FileRepoInternari("participari.txt")

repo_pacienti = RepoPacienti()
file_repo_pacienti = FileRepoPacienti("pacienti.txt")

service_pacienti = ServicePacienti(repo_pacienti, file_repo_pacienti)

class UI:
    def __init__(self, service_pacienti,service_internari):
        self.__service_pacienti = service_pacienti
        self.__service_internari = service_internari

    def afisare(self, lista):
        for element in lista:
            print(element)

    def run_ui(self):
        while True:
            print("1. Afisare pacienti cu nume dat")
            print("2. Afisare pacienti cu mai mult de 2 internari")
            print("3. Exit")
            choice = input("Alege optiunea ta: ")

            if choice == "1":
                nume = input("Introdu numele pacientului cautat: ")
                self.afisare(self.__service_pacienti.afisare_pacienti_nume(nume))
            elif choice == "2":
                self.afisare(self.__service_internari.afisare_peste_2_internari())

            elif choice == "3":
                break

            else:
                print("Optiune invalida!")