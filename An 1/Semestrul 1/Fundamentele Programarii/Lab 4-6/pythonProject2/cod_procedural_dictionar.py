import datetime
def create_travel_package(data_inceput, data_sfarsit, destinatie, pret):
    return {
        "data_inceput": data_inceput,
        "data_sfarsit": data_sfarsit,
        "destinatie": destinatie,
        "pret": pret
    }

def get_data_inceput(pachet):
        "Obtine data de inceput al pachetului de calatorie"
        return pachet["data_inceput"]

def set_data_inceput(pachet, data_inceput):
        "Seteaza data de inceput al pachetului de calatorie "
        pachet["data_inceput"] = data_inceput

def get_data_sfarsit(pachet):
        "Obtine data de sfarsit al pachetului de calatorie"
        return pachet["data_sfarsit"]

def set_data_sfarsit(pachet, data_sfarsit):
        "Seteaza data de sfarsit al pachetului de calatorie"
        pachet["data_sfarsit"] = data_sfarsit

def get_destinatie(pachet):
        "Obtine destinatia pachetului de calatorie"
        return pachet["destinatie"]

def set_destinatie(pachet, destinatie):
        "Seteaza destinatia pachetului de calatorie"
        pachet["destinatie"] = destinatie

def get_pret(pachet):
        "Obtine pretul pachetului de calatorie"
        return pachet["pret"]

def set_pret(pachet, pret):
        "Seteaza pretul pachetului de calatorie"
        pachet["pret"] = pret

def afisare(lista):
    "Afiseaza o lista transmisa"
    for index in range(len(lista)):
        pachet = lista[index]
        print(f"Pachet {index + 1}:\n{pachet}\n")



def salveaza(agency):
        "Salveaza o copie a pachetelor de calatorie"
        copie = [(get_data_inceput(pachet), get_data_sfarsit(pachet), get_destinatie(pachet),
                               get_pret(pachet)) for pachet in agency["pachete"]]
        agency["salvare"].append(copie)

def undo(agency):
        "Reface ultima operatie care a dus la modificarea pachetelor de calatorie"
        if agency["salvare"]:
            agency["pachete"] = agency["salvare"].pop()

def get_pachet(agency, index):
        "Obtine pachetul de calatorie"
        return agency["pachete"][index]

def adauga_pachet(agency, pachet):
        "Adauga un pachet de calatorie la lista de pachete de calatorie"
        agency["pachete"].append(pachet)
def adaugare_pachet(data_inceput, data_sfarsit, destinatie, pret):
        "Creeaza un pachet de calatorie si il adauga la lista de pachete de calatorie"
        pachet = create_travel_package(data_inceput, data_sfarsit, destinatie, pret)
        salveaza(agency)
        agency["salvare"].append(agency["pachete"].copy())
        adauga_pachet(agency, pachet)

def stergere_pachet(agency, index):
        "Sterge un pachet de calatorie"
        agency["pachete"].pop(index)

def modificare_pachet(agency, index, data_inceput, data_sfarsit, destinatie, pret):
        "Modifica un pachet de calatorie"
        if 0 <= index and index < len(agency["pachete"]):
            pachet = get_pachet(index)
            set_data_inceput(pachet, data_inceput)
            set_data_sfarsit(pachet, data_sfarsit)
            set_destinatie(pachet, destinatie)
            set_pret(pachet, pret)

def afisare_pachete(agency):
        "Afiseaza pachetele de calatorie"
        for index in range(len(agency["pachete"])):
            pachet = get_pachet(agency, index)
            print(f"Pachet {index + 1}:")
            print(pachet)

def stergere_destinatie(agency, destinatie):
        "Sterge pachetele de calatorie pentru o destinatie data"
        index = 0
        while index < len(agency["pachete"]):
            pachet = get_pachet(agency, index)
            if destinatie == get_destinatie(pachet):
                stergere_pachet(agency, index)
            else: index+= 1
        return agency["pachete"]

def stergere_durata(agency, durata):
        "Sterge pachetele de calatorie care au o durata mai scurta decat un numar de zile dat"
        index = 0
        while index < len(agency["pachete"]):
            pachet = get_pachet(agency, index)
            data_inceput = get_data_inceput(pachet)
            zi, luna, an = data_inceput.split(".")
            data_inceput_cal = datetime.datetime(int(an), int(luna), int(zi))
            data_sfarsit = get_data_sfarsit(pachet)
            zi, luna, an = data_sfarsit.split(".")
            data_sfarsit_cal = datetime.datetime(int(an), int(luna), int(zi))
            perioada = data_sfarsit_cal - data_inceput_cal
            if perioada < datetime.timedelta(days=int(durata)):
                stergere_pachet(agency, index)
            else: index += 1
        return agency["pachete"]

def stergere_pret(agency, pret):
        "Sterge pachetele de calatorie care au un pret mai mare decat o suma data"
        index = 0
        while index < len(agency["pachete"]):
            pachet = get_pachet(agency, index)
            pret_pachet = get_pret(pachet)
            if int(pret_pachet) > int(pret):
                stergere_pachet(agency, index)
            else: index += 1
        return agency["pachete"]

def cautare_interval(agency, data_inceput_verif, data_sfarsit_verif):
        "Cauta si returneaza pachetele de calatorie care presupun un sejur intr un interval dat"
        lista = []
        for index in range(len(agency["pachete"])):
            pachet = get_pachet(agency, index)
            data_inceput = get_data_inceput(pachet)
            zi, luna, an = data_inceput.split(".")
            data_inceput_noua = an + luna + zi
            data_sfarsit = get_data_sfarsit(pachet)
            zi, luna, an = data_sfarsit.split(".")
            data_sfarsit_noua = an + luna + zi
            zi, luna, an = data_inceput_verif.split(".")
            data_inceput_verif_noua = an + luna + zi
            zi, luna, an = data_sfarsit_verif.split(".")
            data_sfarsit_verif_noua = an + luna + zi
            if int(data_inceput_verif_noua) <= int(data_inceput_noua) and int(data_inceput_verif_noua) <= int(data_sfarsit_noua) and int(data_sfarsit_verif_noua) >= int(data_sfarsit_noua) and int(data_sfarsit_verif_noua) >= int(data_inceput_noua):
                lista.append(pachet)
        return lista
def cautare_destinatie_pret(agency, destinatie, pret):
        "Cauta si returneaza pachetele de calatorie cu o destinatie data si un pret mai mic decat o suma data"
        lista = []
        for index in range(len(agency["pachete"])):
            pachet = get_pachet(agency, index)
            if destinatie == get_destinatie(pachet) and int(get_pret(pachet)) < int(pret):
                lista.append(pachet)
        return lista
def cautare_data_sfarsit(agency, data_sfarsit_verif):
        "Cauta si returneaza pachetele de calatorie cu o anumita data de sfarsit"
        lista = []
        for index in range(len(agency["pachete"])):
            pachet = get_pachet(agency, index)
            data_sfarsit = get_data_sfarsit(pachet)
            zi, luna, an = data_sfarsit.split(".")
            data_sfarsit_noua = an + luna + zi
            zi, luna, an = data_sfarsit_verif.split(".")
            data_sfarsit_verif_noua = an + luna + zi
            if data_sfarsit_verif_noua == data_sfarsit_noua:
                lista.append(pachet)
        return lista

def raport_destinatie(agency, destinatie):
        "Returneaza pachetele de calatorie cu o destinatie data"
        lista = []
        for index in range(len(agency["pachete"])):
            pachet = get_pachet(agency, index)
            if destinatie == get_destinatie(pachet):
                lista.append(pachet)
        return lista
def raport_perioada(agency, data_inceput, data_sfarsit):
        "Returneaza pachetele de calatorie disponibile intr o anumita perioada citita de la tastatura in ordine crescatoare a pretului"
        lista = []
        for pachet in agency["pachete"]:
            if data_inceput == get_data_inceput(pachet) and data_sfarsit == get_data_sfarsit(pachet):
                lista.append(pachet)
        lista_crescatoare = sorted(lista, key=lambda x: x.get_pret())
        return lista_crescatoare
def raport_medie_pret_destinatie(agency, destinatie):
        "Returneaza media de pret pentru o destinatie data"
        suma_pret = 0
        nr = 0
        for pachet in agency["pachete"]:
            if destinatie == get_destinatie(pachet):
                pret = get_pret(pachet)
                suma_pret += int(pret)
                nr+=1
        return int(suma_pret//nr)

def filtrare_eliminare_destinatie_pret(agency, destinatie, pret):
        "Returneaza pachetele de calatorie cu o destinatie anume care au un pret mai mic sau egal cu o suma data"
        lista = []
        for index in range(len(agency["pachete"])):
            pachet = get_pachet(agency, index)
            if destinatie == get_destinatie(pachet) and int(get_pret(pachet)) < int(pret):
                lista.append(pachet)
        return lista

def filtrare_eliminare_luna(agency, luna):
        "Returneaza pachetele de calatorie in care sejurul nu presupune zile dintr o anumita luna"
        lista = []
        for pachet in agency["pachete"]:
            data_sfarsit = get_data_sfarsit(pachet)
            zi_sfarsit, luna_sfarsit, an_sfarsit = data_sfarsit.split(".")
            data_inceput = get_data_inceput(pachet)
            zi_inceput, luna_inceput, an_inceput = data_inceput.split(".")
            if int(luna_inceput) != int(luna) and int(luna_sfarsit) != luna:
                lista.append(pachet)
        return lista

"""
def teste():
    agency = TravelAgency()

    pachet1 = TravelPackage("24.08.2023", "30.08.2023", "maiahi", 500)
    pachet2 = TravelPackage("25.08.2023", "29.08.2023", "maiahu", 600)
    pachet3 = TravelPackage("25.09.2023", "30.09.2023", "maiaha", 450)
    pachet4 = TravelPackage("01.09.2023", "10.09.2023", "maiahi", 700)
    pachet5 = TravelPackage("03.09.2023", "13.09.2023", "maiahi", 1000)
    pachet6 = TravelPackage("21.08.2023", "30.08.2023", "maiahaha", 900)

    agency.adauga_pachet(pachet1)
    agency.adauga_pachet(pachet2)
    agency.adauga_pachet(pachet3)
    agency.adauga_pachet(pachet4)
    agency.adauga_pachet(pachet5)
    agency.adauga_pachet(pachet6)

    data_inceput_verif = "23.08.2023"
    data_sfarsit_verif = "31.08.2023"

    rezultat_cautare_interval = [pachet1,pachet2]
    assert agency.cautare_interval(data_inceput_verif,  data_sfarsit_verif) == rezultat_cautare_interval

    destinatie = "maiahi"
    pret = "1000"
    rezultat_cautare_destinatie_pret = [pachet1, pachet4]
    assert agency.cautare_destinatie_pret(destinatie, pret) == rezultat_cautare_destinatie_pret

    data_sfarsit = "30.08.2023"
    rezultat_cautare_data_sfarsit = [pachet1, pachet6]
    assert agency.cautare_data_sfarsit(data_sfarsit) == rezultat_cautare_data_sfarsit

    destinatie = "maiahi"
    rezultat_raport_destinatie = [pachet1, pachet4, pachet5]
    assert agency.raport_destinatie(destinatie) == rezultat_raport_destinatie

    data_inceput = "24.08.2023"
    data_sfarsit = "30.08.2023"
    rezultat_raport_perioada = [pachet1]
    assert agency.raport_perioada(data_inceput, data_sfarsit) == rezultat_raport_perioada

    destinatie = "maiahi"
    rezultat_raport_medie_pret_destinatie = "733"
    assert agency.raport_medie_pret_destinatie(destinatie) == int(rezultat_raport_medie_pret_destinatie)

    destinatie = "maiahi"
    pret = "800"
    rezultat_filtrare_eliminare_destinatie_pret = [pachet1, pachet4]
    assert agency.filtrare_eliminare_destinatie_pret(destinatie, pret) == rezultat_filtrare_eliminare_destinatie_pret

    luna = "9"
    rezultat_filtrare_eliminare_luna = [pachet1, pachet2, pachet6]
    assert agency.filtrare_eliminare_luna(luna) == rezultat_filtrare_eliminare_luna

    destinatie = "maiahaha"
    rezultat_stergere_destinatie = [pachet1,pachet2,pachet3,pachet4,pachet5]
    assert agency.stergere_destinatie(destinatie) == rezultat_stergere_destinatie

    durata = "5"
    rezultat_stergere_durata = [pachet1,pachet3,pachet4,pachet5]
    assert agency.stergere_durata(durata) == rezultat_stergere_durata


    pret = "450"
    rezultat_stergere_pret = [pachet3]
    assert agency.stergere_pret(pret) == rezultat_stergere_pret

"""

agency = {
        "pachete": [],
        "salvare": []
    }
#teste()

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
            salveaza(agency)

            adaugare_pachet(pachet, data_inceput, data_sfarsit, destinatie, pret)
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
        print("1. Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la tastatură ")
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
