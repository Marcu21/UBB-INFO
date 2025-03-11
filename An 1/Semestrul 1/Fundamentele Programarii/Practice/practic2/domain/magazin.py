class Magazin:
    def __init__(self, id, denumire, pret):
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret

    def get_id(self):
        return self.__id

    def get_denumire(self):
        return self.__denumire


    def get_pret(self):
        return self.__pret

    def set_id(self, idnou):
        self.__id = idnou

    def set_denumire(self, denumirenoua):
        self.__denumire = denumirenoua

    def set_pret(self, pretnou):
        self.__pret = pretnou

    def __str__(self):
        return f"{self.__id},{self.__denumire},{self.__pret}\n"