class Examen:
    def __init__(self, data, ora, materia, sesiune):
        self.__data = data
        self.__ora = ora
        self.__materia = materia
        self.__sesiune = sesiune

    def get_data(self):
        return self.__data

    def get_ora(self):
        return self.__ora

    def get_materia(self):
        return self.__materia

    def get_sesiune(self):
        return self.__sesiune

    def set_data(self, data_noua):
        self.__data = data_noua

    def set_ora(self, ora_noua):
        self.__ora = ora_noua

    def set_materia(self, materia_noua):
        self.__materia = materia_noua

    def set_sesiune(self, sesiune_noua):
        self.__sesiune = sesiune_noua

    def __str__(self):
        return f"{self.__data},{self.__ora},{self.__materia},{self.__sesiune}\n"

