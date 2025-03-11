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