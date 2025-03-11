from TravelAgency import *
from TravelPackage import *
agency = TravelAgency()


def afisare(lista):
    "Afiseaza o lista transmisa"
    for i in range(len(lista)):
        pachet = lista[i]
        print(f"Pachet {i + 1}:\n{pachet}\n")

def run_ui():
    while True:
        print("1. Adaugare")
        print("2. Stergere")
        print("3. Cautare")
        print("4. Rapoarte")
        print("5. Filtrare")
        print("6. Undo")
        print("7. Iesire")
        choice = input("Alege optiunea ta: ")

        if choice == "1":
            print("1. Adauga un pachet de calatorie")
            print("2. Modifica un pachet de calatorie")
            print("3. Afiseaza pachetele de calatorie")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                data_inceput = input("Data inceput: ")
                data_sfarsit = input("Data sfarsit: ")
                destinatie = input("Destinatie: ")
                pret = input("Pret: ")
                agency.salveaza()
                agency.adaugare_pachet(data_inceput, data_sfarsit, destinatie, pret)
            elif choice == "2":
                index = int(input("Numarul pachetului pe care vrei sa il modifici: ")) - 1
                data_inceput = input("Data inceput: ")
                data_sfarsit = input("Data sfarsit: ")
                destinatie = input("Destinatie: ")
                pret = input("Pret: ")
                agency.salveaza()
                agency.modificare_pachet(index, data_inceput, data_sfarsit, destinatie, pret)
            elif choice == "3":
                agency.afisare_pachete()
            else:
                print("Optiune invalida.")
        elif choice == "2":
            print("1. Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată")
            print("2. Ștergerea tuturor pachetelor de călătorie care au o durată mai scurtă decât un număr de zile dat")
            print("3. Ștergerea tuturor pachetelor de călătorie care au prețul mai mare decât o sumă dată")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                destinatie = input("Destinatie: ")
                agency.salveaza()
                agency.stergere_destinatie(destinatie)
                agency.afisare_pachete()
            elif choice == "2":
                durata = input("Numarul de zile: ")
                agency.salveaza()
                agency.stergere_durata(durata)
                agency.afisare_pachete()
            elif choice == "3":
                pret = input("Pret: ")
                agency.salveaza()
                agency.stergere_pret(pret)
                agency.afisare_pachete()
            else:
                print("Optiune invalida.")

        elif choice == "3":
            print("1. Afisarea pachetelor de calatorie care presupun un sejur intr un interval dat")
            print("2. Afisarea pachetelor de calatorie cu o destinatie data si cu pret mai mic decât o suma data.")
            print("3. Afisarea pachetelor de calatorie cu o anumita data de sfarsit")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                data_inceput = input("Data inceput: ")
                data_sfarsit = input("Data sfarsit: ")
                afisare(agency.cautare_interval(data_inceput, data_sfarsit))
            elif choice == "2":
                destinatie = input("Destinatie: ")
                pret = input("Pret: ")
                afisare(agency.cautare_destinatie_pret(destinatie, pret))
            elif choice == "3":
                data_sfarsit_verif = input("Data sfarsit: ")
                afisare(agency.cautare_data_sfarsit(data_sfarsit_verif))
            else:
                print("Optiune invalida.")

        elif choice == "4":
            print("1. Tiparirea numarului de oferte pentru o destinatie data")
            print("2. Tiparirea tuturor pachetelor disponibile intr-o anumita perioada citita")
            print("3. Tiparirea mediei de pret pentru o destinatie data")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                destinatie = input("Destinatie: ")
                afisare(agency.raport_destinatie(destinatie))
            elif choice == "2":
                data_inceput = input("Data inceput: ")
                data_sfarsit = input("Data sfarsit: ")
                afisare(agency.raport_perioada(data_inceput, data_sfarsit))
            elif choice == "3":
                destinatie = input("Destinatie: ")
                print(agency.raport_medie_pret_destinatie(destinatie))
            else:
                print("Optiune invalida.")

        elif choice == "5":
            print(
                "1. Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la tastatură ")
            print("2. Eliminarea ofertelor în care sejurul presupune zile dintr-o anumită lună ")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                destinatie = input("Destinatie: ")
                pret = input("Pret: ")
                afisare(agency.filtrare_eliminare_destinatie_pret(destinatie, pret))
            elif choice == "2":
                luna = input("Luna: ")
                afisare(agency.filtrare_eliminare_luna(luna))
            else:
                print("Optiune invalida.")

        elif choice == "6":
            agency.undo()
            agency.afisare_pachete()

        elif choice == "7":
            break

        else:
            print("Optiune invalida.")