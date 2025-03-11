class Internare:
    def __init__(self, cod_internare, id_pacient, diagnostic, data_internarii, data_externarii):
        self.__cod_internare = cod_internare
        self.__id_pacient = id_pacient
        self.__diagnostic = diagnostic
        self.__data_internarii = data_internarii
        self.__data_externarii = data_externarii

    def get_cod_internare(self):
        return self.__cod_internare

    def get_id_pacient(self):
        return self.__id_pacient

    def get_diagnostic(self):
        return self.__diagnostic

    def get_data_internarii(self):
        return self.__data_internarii

    def get_data_externarii(self):
        return self.__data_externarii

    def __str__(self):
        return f"{self.__cod_internare},{self.__id_pacient},{self.__diagnostic},{self.__data_internarii},{self.__data_externarii}"