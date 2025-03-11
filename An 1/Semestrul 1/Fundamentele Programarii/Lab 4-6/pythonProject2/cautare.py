from TravelPackage import TravelPackage
from TravelAgency import TravelAgency
class TravelAgency:
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
            if int(data_inceput_verif_noua) <= int(data_inceput_noua) and int(data_inceput_verif_noua) <= int(
                    data_sfarsit_noua) and int(data_sfarsit_verif_noua) >= int(data_sfarsit_noua) and int(
                    data_sfarsit_verif_noua) >= int(data_inceput_noua):
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

