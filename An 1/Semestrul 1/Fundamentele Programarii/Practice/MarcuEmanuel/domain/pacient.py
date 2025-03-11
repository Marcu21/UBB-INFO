class Pacient:
    def __init__(self, id_pacient, nume, adresa, data_nasterii):
        self.__id_pacient = id_pacient
        self.__nume = nume
        self.__adresa = adresa
        self.__data_nasterii = data_nasterii

    def get_id_pacient(self):
        return self.__id_pacient

    def get_nume(self):
        return self.__nume

    def get_adresa(self):
        return self.__adresa

    def get_data_nasterii(self):
        return self.__data_nasterii

    def set_id_pacient(self, id_nou):
        self.__id_pacient = id_nou

    def set_nume(self, nume_nou):
        self.__nume = nume_nou

    def set_adresa(self, adresa_noua):
        self.__adresa = adresa_noua

    def set_data_nasterii(self, data_nasterii_noua):
        self.__data_nasterii = data_nasterii_noua

    def __str__(self):
        return f"{self.__id_pacient},{self.__nume},{self.__adresa},{self.__data_nasterii}"