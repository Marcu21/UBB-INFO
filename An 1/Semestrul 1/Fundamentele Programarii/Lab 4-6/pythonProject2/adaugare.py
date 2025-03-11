from TravelPackage import TravelPackage
from TravelAgency import TravelAgency
class TravelAgency:
    def adauga_pachet(self, pachet):
        "Adauga un pachet de calatorie la lista de pachete de calatorie"
        self.__pachete.append(pachet)

    def adaugare_pachet(self, data_inceput, data_sfarsit, destinatie, pret):
        "Creeaza un pachet de calatorie si il adauga la lista de pachete de calatorie"
        pachet = TravelPackage(data_inceput, data_sfarsit, destinatie, pret)
        self.adauga_pachet(pachet)

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

