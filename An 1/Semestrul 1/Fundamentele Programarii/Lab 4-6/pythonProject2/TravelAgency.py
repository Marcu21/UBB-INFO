import datetime
from TravelPackage import TravelPackage
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
        if 0 <= int(index) and int(index) < len(self.__pachete):
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

