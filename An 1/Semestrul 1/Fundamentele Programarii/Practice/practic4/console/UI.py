from domain.emisiuni import *
from domain.validator import *
from persistenta.repository import *
from business.service import *

validator = ValidatorEmisiune()
repo = RepositoryEmisiuni("emisiuni.txt")
service = ServiceEmisiuni(repo, validator)


def run_ui():
    while True:
        print("1. Adaugare")
        print("2. Modificare")
        print("3. Stergere")
        print("4. Program aleator")
        print("5. Afisare emisiuni")
        print("6. Blocheaza tip emisiune")
        if service.tip_blocat() != '':
            print("Tipul emisiunii blocate: ", service.tip_blocat())
        choice = input(">>>>")
        if choice == "1":
            nume = input("nume: ")
            tip = input("tip:  ")
            durata = input("durata: ")
            descriere = input("descriere: ")
            try:
                service.adauga(nume, tip, durata, descriere)
            except ValueError as ve:
                print(ve)
        elif choice == "2":
            nume = input("nume: ")
            tip = input("tip:  ")
            durata = input("durata: ")
            descriere = input("descriere: ")
            try:
                service.modifica(nume, tip, durata, descriere)
            except ValueError as ve:
                print(ve)
            except Exception as ex:
                print(ex)
        elif choice == "3":
            nume = input("nume: ")
            tip = input("tip:  ")
            try:
                service.sterge(nume, tip)
            except Exception as ex:
                print(ex)

        elif choice == "4":
            ora_inceput = int(input("ora inceput: "))
            ora_sfarsit = int(input("ora sfarsit: "))
            program = service.program_aleator(ora_inceput, ora_sfarsit)
            for emisiune in program:
                print(str(ora_inceput) + ' '+ str(emisiune))
                ora_inceput += int(emisiune.get_durata())

        elif choice == "5":
            l = service.get_all()
            for emisiune in l:
                print(repr(emisiune))

        elif choice == "6":
            tip = input("tip: ")
            service.blocheaza_tip(tip)

        else:
            break
