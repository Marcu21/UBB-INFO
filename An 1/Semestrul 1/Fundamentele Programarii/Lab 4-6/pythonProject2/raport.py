from TravelPackage import TravelPackage
from TravelAgency import TravelAgency
class TravelAgency:
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