from TravelPackage import TravelPackage
from TravelAgency import TravelAgency
class TravelAgency:
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