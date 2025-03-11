from TravelAgency import *
from TravelPackage import *
agency = TravelAgency()


def afisare(lista):
    "Afiseaza o lista transmisa"
    for i in range(len(lista)):
        pachet = lista[i]
        print(f"Pachet {i + 1}:\n{pachet}\n")

def run_ui2():
    while True:
        comanda = input("Introdu comanda ta: ")
        instructiuni = comanda.split(";")
        for instructiune in instructiuni:
            cuv = instructiune.split(" ")
            if (len(cuv)) < 0:
                continue
            if cuv[0] == "Adauga1":
                if (len(cuv)) != 5:
                    print("Comanda incorecta")
                    continue
                else:
                    agency.salveaza()
                    agency.adaugare_pachet(cuv[1], cuv[2], cuv[3], cuv[4])
                    continue
            if cuv[0] == "Adauga2":
                if (len(cuv)) != 6:
                    print("Comanda incorecta")
                    continue
                else:
                    agency.salveaza()
                    agency.modificare_pachet(int(cuv[1])-1, cuv[2], cuv[3], cuv[4], cuv[5])
                    continue
            if cuv[0] == "Afisare":
                if (len(cuv)) != 1:
                    print("Comanda incorecta")
                else:
                    agency.afisare_pachete()
            if cuv[0] == "Stergere1":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    agency.salveaza()
                    agency.stergere_destinatie(cuv[1])
                    agency.afisare_pachete()
            if cuv[0] == "Stergere2":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    agency.salveaza()
                    agency.stergere_durata(cuv[1])
                    agency.afisare_pachete()
            if cuv[0] == "Stergere3":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    agency.salveaza()
                    agency.stergere_pret(cuv[1])
                    agency.afisare_pachete()
            if cuv[0] == "Cautare1":
                if (len(cuv)) != 3:
                    print("Comanda incorecta")
                else:
                    afisare(agency.cautare_interval(cuv[1], cuv[2]))
            if cuv[0] == "Cautare2":
                if (len(cuv)) != 3:
                    print("Comanda incorecta")
                else:
                    afisare(agency.cautare_destinatie_pret(cuv[1], cuv[2]))
            if cuv[0] == "Cautare3":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    afisare(agency.cautare_data_sfarsit(cuv[1]))
            if cuv[0] == "Raport1":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    afisare(agency.raport_destinatie(cuv[1]))
            if cuv[0] == "Raport2":
                if (len(cuv)) != 3:
                    print("Comanda incorecta")
                else:
                    afisare(agency.raport_perioada(cuv[1], cuv[2]))
            if cuv[0] == "Raport3":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    print(agency.raport_medie_pret_destinatie(cuv[1]))
            if cuv[0] == "Filtrare1":
                if (len(cuv)) != 3:
                    print("Comanda incorecta")
                else:
                    afisare(agency.filtrare_eliminare_destinatie_pret(cuv[1], cuv[2]))
            if cuv[0] == "Filtrare2":
                if (len(cuv)) != 2:
                    print("Comanda incorecta")
                else:
                    afisare(agency.filtrare_eliminare_luna(cuv[1]))
            if cuv[0] == "Undo":
                if (len(cuv)) != 1:
                    print("Comanda incorecta")
                else:
                    agency.undo()
            else:
                continue
