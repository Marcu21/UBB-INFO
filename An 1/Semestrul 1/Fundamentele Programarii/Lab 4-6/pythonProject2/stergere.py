from TravelPackage import TravelPackage
class TravelAgency:
    def stergere_pachet(self, index):
        "Sterge un pachet de calatorie"
        self.__pachete.pop(index)

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