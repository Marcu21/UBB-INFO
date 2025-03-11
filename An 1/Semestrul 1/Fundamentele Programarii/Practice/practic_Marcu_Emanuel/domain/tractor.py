class Tractor:
    def __init__(self, id, denumire, pret, model, data):
        '''
        Creeaza un tractor
        :param id: int
        :param denumire: string
        :param pret: int
        :param model: string
        :param data: string
        '''
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret
        self.__model = model
        self.__data = data

    def get_id(self):
        '''
        Returneaza id-ul unui tractor
        :return: int
        '''
        return int(self.__id)

    def get_denumire(self):
        '''
        Returneaza denumirea unui tractor
        :return: string
        '''
        return self.__denumire

    def get_pret(self):
        '''
        Returneaza pretul unui tractor
        :return: int
        '''
        return int(self.__pret)

    def get_model(self):
        '''
        Returneaza modelul unui tractor
        :return: string
        '''
        return self.__model

    def get_data(self):
        '''
        Returneaza data unui tractor
        :return: string
        '''
        return self.__data

    def set_id(self, id_nou):
        '''
        Seteaza un id nou pentru un tractor
        :param id_nou: int
        :return:
        '''
        self.__id = id_nou

    def set_denumire(self, denumire_noua):
        '''
        Seteaza o denumire noua pentru un tractor
        :param denumire_noua: string
        :return:
        '''
        self.__denumire = denumire_noua

    def set_pret(self, pret_nou):
        '''
        Seteaza un pret nou pentru un tractor
        :param pret_nou: int
        :return:
        '''
        self.__pret = pret_nou

    def set_model(self, model_nou):
        '''
        Seteaza un model nou pentru un tractor
        :param model_nou: string
        :return:
        '''
        self.__model = model_nou

    def set_data(self, data_noua):
        '''
        Seteaza o data noua pentru un tractor
        :param data_noua: string
        :return:
        '''
        self.__data = data_noua

    def __repr__(self):
        '''
        :return: Reprezentarea tractorului in fisier
        '''
        return f"{self.__id},{self.__denumire},{self.__pret},{self.__model},{self.__data}"

    def __str__(self):
        '''
        :return: Reprezentarea tractorului pentru utilizator
        '''
        return f"{self.__id} {self.__denumire} {self.__pret} {self.__model} {self.__data}"