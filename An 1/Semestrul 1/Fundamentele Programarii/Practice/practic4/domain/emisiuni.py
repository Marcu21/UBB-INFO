class Emisiuni:
    def __init__(self, nume, tip, durata, descriere):
        self.__nume = nume
        self.__tip = tip
        self.__durata = durata
        self.__descriere = descriere

    def get_nume(self):
        return self.__nume

    def get_tip(self):
        return self.__tip

    def get_durata(self):
        return self.__durata

    def get_descriere(self):
        return self.__descriere

    def set_nume(self, nume):
        self.__nume = nume

    def set_tip(self, tip):
        self.__tip = tip

    def set_durata(self, durata):
        self.__durata = durata

    def set_descriere(self, descriere):
        self.__descriere = descriere

    def __repr__(self):
        return f"{self.__nume},{self.__tip},{self.__durata},{self.__descriere}"

    def __str__(self):
        return f"{self.__nume} {self.__tip} {self.__descriere}\n"