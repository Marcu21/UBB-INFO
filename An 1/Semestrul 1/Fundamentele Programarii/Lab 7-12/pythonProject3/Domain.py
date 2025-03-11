class Film:
    def __init__(self, id_film, titlu, descriere, gen):
        self.__id_film = id_film
        self.__titlu = titlu
        self.__descriere = descriere
        self.__gen = gen

    def get_id_film(self):
        return self.__id_film

    def get_titlu(self):
        return self.__titlu

    def get_descriere(self):
        return self.__descriere

    def get_gen(self):
        return self.__gen

    def set_id_film(self, id_nou):
        self.__id_film = id_nou

    def set_titlu(self, titlu_nou):
        self.__titlu = titlu_nou

    def set_descriere(self, descriere_noua):
        self.__descriere = descriere_noua

    def set_gen(self, gen_nou):
        self.__gen = gen_nou

    def __str__(self):
        return f"[{self.__id_film}]{self.__titlu}: {self.__descriere}| {self.__gen}"

class Client:
    def __init__(self, id_client, nume, prenume, cnp):
        self.__id_client = id_client
        self.__nume = nume
        self.__prenume = prenume
        self.__cnp = cnp

    def get_id_client(self):
        return self.__id_client

    def get_nume(self):
        return self.__nume

    def get_prenume(self):
        return self.__prenume

    def get_cnp(self):
        return self.__cnp

    def set_id_client(self, id_client_nou):
        self.__id_client = id_client_nou

    def set_nume(self, nume_nou):
        self.__nume = nume_nou

    def set_prenume(self, prenume_nou):
        self.__prenume = prenume_nou

    def set_cnp(self, cnp_nou):
        self.__cnp = cnp_nou

    def __str__(self):
        return f"[{self.__id_client}] {self.__nume} {self.__prenume}: {self.__cnp}"

class FilmInchiriat:
    def __init__(self, id_film, nr_inchirieri):
        self.__id_film = id_film
        self.__numar_inchirieri = nr_inchirieri

    def get_id_film(self):
        return self.__id_film

    def get_numar_inchirieri(self):
        return self.__numar_inchirieri

    def set_id_film(self, id_nou):
        self.__id_film = id_nou

    def set_numar_inchirieri(self, nr_inchirieri_nou):
        self.__numar_inchirieri = nr_inchirieri_nou


class ClientInchiriator:
    def __init__(self, id_client, nr_inchirieri):
        self.__id_client = id_client
        self.__numar_inchirieri = nr_inchirieri

    def get_id_client(self):
        return self.__id_client

    def get_numar_inchirieri(self):
        return self.__numar_inchirieri

    def set_id_client(self, id_nou):
        self.__id_client = id_nou

    def set_numar_inchirieri(self, nr_inchirieri_nou):
        self.__numar_inchirieri = nr_inchirieri_nou
