import datetime

def create_travel_package(data_inceput, data_sfarsit, destinatie, pret):
    return {
        "data_inceput": data_inceput,
        "data_sfarsit": data_sfarsit,
        "destinatie": destinatie,
        "pret": pret
    }

def get_data_inceput(pachet):
    return pachet["data_inceput"]

def set_data_inceput(pachet, data_inceput):
    pachet["data_inceput"] = data_inceput

def get_data_sfarsit(pachet):
    return pachet["data_sfarsit"]

def set_data_sfarsit(pachet, data_sfarsit):
    pachet["data_sfarsit"] = data_sfarsit

def get_destinatie(pachet):
    return pachet["destinatie"]

def set_destinatie(pachet, destinatie):
    pachet["destinatie"] = destinatie

def get_pret(pachet):
    return pachet["pret"]

def set_pret(pachet, pret):
    pachet["pret"] = pret

def afisare(lista):
    for index, pachet in enumerate(lista, start=1):
        print(f"Pachet {index}:\nData inceput: {pachet['data_inceput']}\nData sfarsit: {pachet['data_sfarsit']}\nDestinatie: {pachet['destinatie']}\nPret: {pachet['pret']}")

def salveaza(agency):
    copie = [pachet.copy() for pachet in agency["pachete"]]
    agency["salvare"].append(copie)

def undo(agency):
    if agency["salvare"]:
        agency["pachete"] = agency["salvare"].pop()

def get_pachet(agency, index):
    return agency["pachete"][index]

def adauga_pachet(agency, pachet):
    agency["pachete"].append(pachet)

def adaugare_pachet(agency, data_inceput, data_sfarsit, destinatie, pret):
    pachet = create_travel_package(data_inceput, data_sfarsit, destinatie, pret)
    salveaza(agency)
    adauga_pachet(agency, pachet)

def stergere_pachet(agency, index):
    if 0 <= index < len(agency["pachete"]):
        agency["pachete"].pop(index)

def modificare_pachet(agency, index, data_inceput, data_sfarsit, destinatie, pret):
    if 0 <= index < len(agency["pachete"]):
        pachet = get_pachet(agency, index)
        set_data_inceput(pachet, data_inceput)
        set_data_sfarsit(pachet, data_sfarsit)
        set_destinatie(pachet, destinatie)
        set_pret(pachet, pret)

def afisare_pachete(agency):
    afisare(agency["pachete"])

def stergere_destinatie(agency, destinatie):
    index = 0
    while index < len(agency["pachete"]):
        pachet = get_pachet(agency, index)
        if destinatie == get_destinatie(pachet):
            stergere_pachet(agency, index)
        else:
            index += 1
    return agency["pachete"]

def stergere_durata(agency, durata):
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
        else:
            index += 1
    return agency["pachete"]

def stergere_pret(agency, pret):
    index = 0
    while index < len(agency["pachete"]):
        pachet = get_pachet(agency, index)
        pret_pachet = get_pret(pachet)
        if int(pret_pachet) > int(pret):
            stergere_pachet(agency, index)
        else:
            index += 1
    return agency["pachete"]

def cautare_interval(agency, data_inceput_verif, data_sfarsit_verif):
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
    lista = []
    for index in range(len(agency["pachete"])):
        pachet = get_pachet(agency, index)
        if destinatie == get_destinatie(pachet) and int(get_pret(pachet)) < int(pret):
            lista.append(pachet)
    return lista

def cautare_data_sfarsit(agency, data_sfarsit_verif):
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
    lista = []
    for index in range(len(agency["pachete"])):
        pachet = get_pachet(agency, index)
        if destinatie == get_destinatie(pachet):
            lista.append(pachet)
    return lista

def raport_perioada(agency, data_inceput, data_sfarsit):
    lista = []
    for pachet in agency["pachete"]:
        if data_inceput == get_data_inceput(pachet) and data_sfarsit == get_data_sfarsit(pachet):
            lista.append(pachet)
    lista_crescatoare = sorted(lista, key=lambda x: x['pret'])
    return lista_crescatoare

def raport_medie_pret_destinatie(agency, destinatie):
    suma_pret = 0
    nr = 0
    for pachet in agency["pachete"]:
        if destinatie == get_destinatie(pachet):
            pret = get_pret(pachet)
            suma_pret += int(pret)
            nr += 1
    return int(suma_pret // nr)

def filtrare_eliminare_destinatie_pret(agency, destinatie, pret):
    lista = []
    for index in range(len(agency["pachete"])):
        pachet = get_pachet(agency, index)
        if destinatie == get_destinatie(pachet) and int(get_pret(pachet)) <= int(pret):
            lista.append(pachet)
    return lista

def filtrare_eliminare_luna(agency, luna):
    lista = []
    for pachet in agency["pachete"]:
        data_sfarsit = get_data_sfarsit(pachet)
        zi_sfarsit, luna_sfarsit, an_sfarsit = data_sfarsit.split(".")
        data_inceput = get_data_inceput(pachet)
        zi_inceput, luna_inceput, an_inceput = data_inceput.split(".")
        if int(luna_inceput) != int(luna) and int(luna_sfarsit) != int(luna):
            lista.append(pachet)
    return lista

def teste():

    pachet1 = create_travel_package("24.08.2023", "30.08.2023", "maiahi", 500)
    pachet2 = create_travel_package("25.08.2023", "29.08.2023", "maiahu", 600)
    pachet3 = create_travel_package("25.09.2023", "30.09.2023", "maiaha", 450)
    pachet4 = create_travel_package("01.09.2023", "10.09.2023", "maiahi", 700)
    pachet5 = create_travel_package("03.09.2023", "13.09.2023", "maiahi", 1000)
    pachet6 = create_travel_package("21.08.2023", "30.08.2023", "maiahaha", 900)

    adauga_pachet(agency, pachet1)
    adauga_pachet(agency, pachet2)
    adauga_pachet(agency, pachet3)
    adauga_pachet(agency, pachet4)
    adauga_pachet(agency, pachet5)
    adauga_pachet(agency, pachet6)

    data_inceput_verif = "23.08.2023"
    data_sfarsit_verif = "31.08.2023"

    rezultat_cautare_interval = [pachet1,pachet2]
    assert cautare_interval(agency, data_inceput_verif,  data_sfarsit_verif) == rezultat_cautare_interval

    destinatie = "maiahi"
    pret = "1000"
    rezultat_cautare_destinatie_pret = [pachet1, pachet4]
    assert cautare_destinatie_pret(agency, destinatie, pret) == rezultat_cautare_destinatie_pret

    data_sfarsit = "30.08.2023"
    rezultat_cautare_data_sfarsit = [pachet1, pachet6]
    assert cautare_data_sfarsit(agency, data_sfarsit) == rezultat_cautare_data_sfarsit

    destinatie = "maiahi"
    rezultat_raport_destinatie = [pachet1, pachet4, pachet5]
    assert raport_destinatie(agency, destinatie) == rezultat_raport_destinatie

    data_inceput = "24.08.2023"
    data_sfarsit = "30.08.2023"
    rezultat_raport_perioada = [pachet1]
    assert raport_perioada(agency, data_inceput, data_sfarsit) == rezultat_raport_perioada

    destinatie = "maiahi"
    rezultat_raport_medie_pret_destinatie = "733"
    assert raport_medie_pret_destinatie(agency, destinatie) == int(rezultat_raport_medie_pret_destinatie)

    destinatie = "maiahi"
    pret = "800"
    rezultat_filtrare_eliminare_destinatie_pret = [pachet1, pachet4]
    assert filtrare_eliminare_destinatie_pret(agency, destinatie, pret) == rezultat_filtrare_eliminare_destinatie_pret

    luna = "9"
    rezultat_filtrare_eliminare_luna = [pachet1, pachet2, pachet6]
    assert filtrare_eliminare_luna(agency, luna) == rezultat_filtrare_eliminare_luna

    destinatie = "maiahaha"
    rezultat_stergere_destinatie = [pachet1,pachet2,pachet3,pachet4,pachet5]
    assert stergere_destinatie(agency, destinatie) == rezultat_stergere_destinatie

    durata = "5"
    rezultat_stergere_durata = [pachet1,pachet3,pachet4,pachet5]
    assert stergere_durata(agency, durata) == rezultat_stergere_durata


    pret = "450"
    rezultat_stergere_pret = [pachet3]
    assert stergere_pret(agency, pret) == rezultat_stergere_pret

agency = {
    "pachete": [],
    "salvare": []
}
copie = [
    (
        get_data_inceput(pachet),
        get_data_sfarsit(pachet),
        get_destinatie(pachet),
        get_pret(pachet)
    ) for pachet in agency["pachete"]
]

teste()

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
            adaugare_pachet(agency, data_inceput, data_sfarsit, destinatie, pret)
        elif choice == "2":
            index = int(input("Numarul pachetului pe care vrei sa il modifici: ")) - 1
            data_inceput = input("Data inceput: ")
            data_sfarsit = input("Data sfarsit: ")
            destinatie = input("Destinatie: ")
            pret = input("Pret: ")
            salveaza(agency)
            modificare_pachet(agency, index, data_inceput, data_sfarsit, destinatie, pret)
        elif choice == "3":
            afisare_pachete(agency)
        else:
            print("Optiune invalida.")
    elif choice == "2":
        print("1. Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată")
        print("2. Ștergerea tuturor pachetelor de călătorie care au o durată mai scurtă decât un număr de zile dat")
        print("3. Ștergerea tuturor pachetelor de călătorie care au prețul mai mare decât o sumă dată")
        choice = input("Alege optiunea ta: ")
        if choice == "1":
            destinatie = input("Destinatie: ")
            salveaza(agency)
            stergere_destinatie(agency, destinatie)
            afisare_pachete(agency)
        elif choice == "2":
            durata = input("Numarul de zile: ")
            salveaza(agency)
            stergere_durata(agency, durata)
            afisare_pachete(agency)
        elif choice == "3":
            pret = input("Pret: ")
            salveaza(agency)
            stergere_pret(agency, pret)
            afisare_pachete(agency)
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
            afisare(cautare_interval(agency, data_inceput, data_sfarsit))
        elif choice == "2":
            destinatie = input("Destinatie: ")
            pret = input("Pret: ")
            afisare(cautare_destinatie_pret(agency, destinatie, pret))
        elif choice == "3":
            data_sfarsit_verif = input("Data sfarsit: ")
            afisare(cautare_data_sfarsit(agency, data_sfarsit_verif))
        else:
            print("Optiune invalida.")

    elif choice == "4":
        print("1. Tiparirea numarului de oferte pentru o destinatie data")
        print("2. Tiparirea tuturor pachetelor disponibile intr-o anumita perioada citita")
        print("3. Tiparirea mediei de pret pentru o destinatie data")
        choice = input("Alege optiunea ta: ")
        if choice == "1":
            destinatie = input("Destinatie: ")
            afisare(raport_destinatie(agency, destinatie))
        elif choice == "2":
            data_inceput = input("Data inceput: ")
            data_sfarsit = input("Data sfarsit: ")
            afisare(raport_perioada(agency, data_inceput, data_sfarsit))
        elif choice == "3":
            destinatie = input("Destinatie: ")
            print(raport_medie_pret_destinatie(agency, destinatie))
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
            afisare(filtrare_eliminare_destinatie_pret(agency, destinatie, pret))
        elif choice == "2":
            luna = input("Luna: ")
            afisare(filtrare_eliminare_luna(agency, luna))
        else:
            print("Optiune invalida.")

    elif choice == "6":
        undo(agency)
        afisare_pachete(agency)

    elif choice == "7":
        break

    else:
        print("Optiune invalida.")
