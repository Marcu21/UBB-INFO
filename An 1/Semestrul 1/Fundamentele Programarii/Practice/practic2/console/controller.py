from domain.magazin import *
from domain.validator import *
from persistenta.repository import *
from business.service import *
validator = Validator()
repo = RepositoryMagazin("magazin.txt")
service = ServiceMagazin(repo, validator)
def run_ui():
    while True:
        print("1. Adauga")
        print("2. Sterge")
        print("3. Filtrare")
        print("4. Undo")
        choice = input("Introdu optiunea ta: ")

        if choice == "1":
            id = input("id: ")
            denumire = input("denumire: ")
            pret = input("pret: ")
            try:
                service.adaugare(id, denumire, pret)
            except Exception as ve:
                print(ve)