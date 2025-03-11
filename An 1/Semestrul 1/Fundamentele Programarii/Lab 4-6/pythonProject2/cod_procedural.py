import datetime
class TravelPackage:
    def __init__(self, data_inceput, data_sfarsit, destinatie, pret):
        "Initializeaza un pachet de calatorie"
        self.__data_inceput = data_inceput
        self.__data_sfarsit = data_sfarsit
        self.__destinatie = destinatie
        self.__pret = pret

    def __str__(self):
        "Returneaza o reprezentare sub forma de sir a unui pachet de calatorie"
        return (f"Destinatie: {self.__destinatie}\nData inceput: {self.__data_inceput}\nData sfarsit: {self.__data_sfarsit}"
                f"\nPret: {self.__pret}")

    def get_data_inceput(self):
        "Obtine data de inceput al pachetului de calatorie"
        return self.__data_inceput

    def set_data_inceput(self, data_inceput):
        "Seteaza data de inceput al pachetului de calatorie "
        self.__data_inceput = data_inceput

    def get_data_sfarsit(self):
        "Obtine data de sfarsit al pachetului de calatorie"
        return self.__data_sfarsit

    def set_data_sfarsit(self, data_sfarsit):
        "Seteaza data de sfarsit al pachetului de calatorie"
        self.__data_sfarsit = data_sfarsit

    def get_destinatie(self):
        "Obtine destinatia pachetului de calatorie"
        return self.__destinatie

    def set_destinatie(self, destinatie):
        "Seteaza destinatia pachetului de calatorie"
        self.__destinatie = destinatie

    def get_pret(self):
        "Obtine pretul pachetului de calatorie"
        return self.__pret

    def set_pret(self, pret):
        "Seteaza pretul pachetului de calatorie"
        self.__pret = pret

def afisare(lista):
    "Afiseaza o lista transmisa"
    for i in range(len(lista)):
        pachet = lista[i]
        print(f"Pachet {i + 1}:\n{pachet}\n")


class Validator:
    def valideaza_pachet(self, pachet):
        erori = ""
        data_inceput = pachet.get_data_inceput()
        zi, luna, an = data_inceput.split(".")
        if pachet.get_data_inceput == "" or (int(zi)>28 and int(luna)==2) or (int(zi)>30 and (int(luna)==4 or int(luna)==6 or int(luna)==9 or int(luna)==11)) or int(zi)>31:
            erori += "data inceput invalida!\n"
        data_sfarsit = pachet.get_data_sfarsit()
        zi, luna, an = data_sfarsit.split(".")
        if pachet.get_data_sfarsit() == "" or (int(zi) > 28 and int(luna) == 2) or (int(zi) > 30 and (int(luna) == 4 or int(luna) == 6 or int(luna) == 9 or int(luna) == 11)) or int(zi) > 31:
            erori += "data sfarsit invalida!\n"
        if pachet.get_destinatie() == "":
            erori += "destinatie invalida!\n"
        if pachet.get_pret() < 0.0:
            erori += "pret invalid!\n"
        if len(erori) > 0:
            raise Exception(erori)


class TravelAgency:
    def __init__(self):
        "Crearea listelor de pachete de calatorie"
        self.__pachete = []
        self.__salvare = []

    def salveaza(self):
        "Salveaza o copie a pachetelor de calatorie"
        copie = [TravelPackage(pachet.get_data_inceput(), pachet.get_data_sfarsit(), pachet.get_destinatie(),
                               pachet.get_pret()) for pachet in self.__pachete]
        self.__salvare.append(copie)

    def undo(self):
        "Reface ultima operatie care a dus la modificarea pachetelor de calatorie"
        if self.__salvare:
            self.__pachete = self.__salvare.pop()

    def get_pachet(self, index):
        "Obtine pachetul de calatorie"
        return self.__pachete[index]

    def adauga_pachet(self, pachet):
        "Adauga un pachet de calatorie la lista de pachete de calatorie"
        self.__pachete.append(pachet)
    def adaugare_pachet(self, data_inceput, data_sfarsit, destinatie, pret):
        "Creeaza un pachet de calatorie si il adauga la lista de pachete de calatorie"
        pachet = TravelPackage(data_inceput, data_sfarsit, destinatie, pret)
        self.adauga_pachet(pachet)

    def stergere_pachet(self, index):
        "Sterge un pachet de calatorie"
        self.__pachete.pop(index)

    def modificare_pachet(self, index, data_inceput, data_sfarsit, destinatie, pret):
        "Modifica un pachet de calatorie"
        if 0 <= index and index < len(self.__pachete):
            pachet = self.get_pachet(index)
            pachet.set_data_inceput(data_inceput)
            pachet.set_data_sfarsit(data_sfarsit)
            pachet.set_destinatie(destinatie)
            pachet.set_pret(pret)

    def afisare_pachete(self):
        "Afiseaza pachetele de calatorie"
        for i in range(len(self.__pachete)):
            pachet = self.get_pachet(i)
            print(f"Pachet {i + 1}:")
            print(pachet)

    def stergere_destinatie(self, destinatie):
        "Sterge pachetele de calatorie pentru o destinatie data"
        index = 0
        while index < len(self.__pachete):
            pachet = self.get_pachet(index)
            if destinatie == pachet.get_destinatie():
                self.stergere_pachet(index)
            else: index+= 1
        return self.__pachete

    def stergere_durata(self, durata):
        "Sterge pachetele de calatorie care au o durata mai scurta decat un numar de zile dat"
        index = 0
        while index < len(self.__pachete):
            pachet = self.get_pachet(index)
            data_inceput = pachet.get_data_inceput()
            zi, luna, an = data_inceput.split(".")
            data_inceput_cal = datetime.datetime(int(an), int(luna), int(zi))
            data_sfarsit = pachet.get_data_sfarsit()
            zi, luna, an = data_sfarsit.split(".")
            data_sfarsit_cal = datetime.datetime(int(an), int(luna), int(zi))
            perioada = data_sfarsit_cal - data_inceput_cal
            if perioada < datetime.timedelta(days=int(durata)):
                self.stergere_pachet(index)
            else: index += 1
        return self.__pachete

    def stergere_pret(self, pret):
        "Sterge pachetele de calatorie care au un pret mai mare decat o suma data"
        index = 0
        while index < len(self.__pachete):
            pachet = self.get_pachet(index)
            pret_pachet = pachet.get_pret()
            if int(pret_pachet) > int(pret):
                self.stergere_pachet(index)
            else: index += 1
        return self.__pachete

    def cautare_interval(self, data_inceput_verif, data_sfarsit_verif):
        "Cauta si returneaza pachetele de calatorie care presupun un sejur intr un interval dat"
        lista = []
        for i in range(len(self.__pachete)):
            pachet = self.get_pachet(i)
            data_inceput = pachet.get_data_inceput()
            zi, luna, an = data_inceput.split(".")
            data_inceput_noua = an + luna + zi
            data_sfarsit = pachet.get_data_sfarsit()
            zi, luna, an = data_sfarsit.split(".")
            data_sfarsit_noua = an + luna + zi
            zi, luna, an = data_inceput_verif.split(".")
            data_inceput_verif_noua = an + luna + zi
            zi, luna, an = data_sfarsit_verif.split(".")
            data_sfarsit_verif_noua = an + luna + zi
            if int(data_inceput_verif_noua) <= int(data_inceput_noua) and int(data_inceput_verif_noua) <= int(data_sfarsit_noua) and int(data_sfarsit_verif_noua) >= int(data_sfarsit_noua) and int(data_sfarsit_verif_noua) >= int(data_inceput_noua):
                lista.append(pachet)
        return lista
    def cautare_destinatie_pret(self, destinatie, pret):
        "Cauta si returneaza pachetele de calatorie cu o destinatie data si un pret mai mic decat o suma data"
        lista = []
        for i in range(len(self.__pachete)):
            pachet = self.get_pachet(i)
            if destinatie == pachet.get_destinatie() and int(pachet.get_pret()) < int(pret):
                lista.append(pachet)
        return lista
    def cautare_data_sfarsit(self, data_sfarsit_verif):
        "Cauta si returneaza pachetele de calatorie cu o anumita data de sfarsit"
        lista = []
        for i in range(len(self.__pachete)):
            pachet = self.get_pachet(i)
            data_sfarsit = pachet.get_data_sfarsit()
            zi, luna, an = data_sfarsit.split(".")
            data_sfarsit_noua = an + luna + zi
            zi, luna, an = data_sfarsit_verif.split(".")
            data_sfarsit_verif_noua = an + luna + zi
            if data_sfarsit_verif_noua == data_sfarsit_noua:
                lista.append(pachet)
        return lista

    def raport_destinatie(self, destinatie):
        "Returneaza pachetele de calatorie cu o destinatie data"
        lista = []
        for i in range(len(self.__pachete)):
            pachet = self.get_pachet(i)
            if destinatie == pachet.get_destinatie():
                lista.append(pachet)
        return lista
    def raport_perioada(self, data_inceput, data_sfarsit):
        "Returneaza pachetele de calatorie disponibile intr o anumita perioada citita de la tastatura in ordine crescatoare a pretului"
        lista = []
        for pachet in self.__pachete:
            if data_inceput == pachet.get_data_inceput() and data_sfarsit == pachet.get_data_sfarsit():
                lista.append(pachet)
        lista_crescatoare = sorted(lista, key=lambda x: x.get_pret())
        return lista_crescatoare
    def raport_medie_pret_destinatie(self, destinatie):
        "Returneaza media de pret pentru o destinatie data"
        suma_pret = 0
        nr = 0
        for pachet in self.__pachete:
            if destinatie == pachet.get_destinatie():
                pret = pachet.get_pret()
                suma_pret += int(pret)
                nr+=1
        return int(suma_pret//nr)

    def filtrare_eliminare_destinatie_pret(self, destinatie, pret):
        "Returneaza pachetele de calatorie cu o destinatie anume care au un pret mai mic sau egal cu o suma data"
        lista = []
        for i in range(len(self.__pachete)):
            pachet = self.get_pachet(i)
            if destinatie == pachet.get_destinatie() and int(pachet.get_pret()) < int(pret):
                lista.append(pachet)
        return lista

    def filtrare_eliminare_luna(self, luna):
        "Returneaza pachetele de calatorie in care sejurul nu presupune zile dintr o anumita luna"
        lista = []
        for pachet in self.__pachete:
            data_sfarsit = pachet.get_data_sfarsit()
            zi_sfarsit, luna_sfarsit, an_sfarsit = data_sfarsit.split(".")
            data_inceput = pachet.get_data_inceput()
            zi_inceput, luna_inceput, an_inceput = data_inceput.split(".")
            if int(luna_inceput) != int(luna) and int(luna_sfarsit) != luna:
                lista.append(pachet)
        return lista


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

    pachet7 = TravelPackage("29.02.2023", "32.08.2023", "", -1)
    try:
        validator = Validator()
        validator.valideaza_pachet(pachet7)
        assert False
    except Exception as ex:
        assert (str(ex) == "data inceput invalida!\ndata sfarsit invalida!\ndestinatie invalida!\npret invalid!\n")

agency = TravelAgency()

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
