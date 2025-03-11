class FilmRepository:
    def __init__(self):
        self.__filme = {}

    def get_film(self, id):
        for film_id, film in self.__filme.items():
            if int(film_id) == int(id):
                return film

    def adaugare_film(self, film):
        id_film = film.get_id_film()
        if id_film in self.__filme:
            raise Exception("id existent!\n")
        self.__filme[id_film] = film

    def stergere_film(self, id):
        self.__filme.pop(id)

    def modifica_film(self, id, id_nou, titlu_nou, descriere_noua, gen_nou):
        film = self.get_film(id)
        film.set_id_film(id_nou)
        film.set_titlu(titlu_nou)
        film.set_descriere(descriere_noua)
        film.set_gen(gen_nou)

    def get_all(self):
        return [self.__filme[x] for x in self.__filme.keys()]

    def afisare_filme(self):
        for film in self.__filme.values():
            if len(film.get_titlu()) > 0:
                print(film)


class ClientRepository:
    def __init__(self):
        self.__clienti = {}

    def get_client(self, id):
        for client_id, client in self.__clienti.items():
            if int(client_id) == int(id):
                return client

    def adaugare_client(self, client):
        id_client = client.get_id_client()
        self.__clienti[id_client] = client

    def stergere_client(self, id):
        self.__clienti.pop(id)

    def modifica_client(self, id, id_nou, nume_nou, prenume_nou, cnp_nou):
        client = self.get_client(id)
        client.set_id_client(id_nou)
        client.set_nume(nume_nou)
        client.set_prenume(prenume_nou)
        client.set_cnp(cnp_nou)

    def get_all(self):
        return list(self.__clienti.values())

    def afisare_clienti(self):
        for client in self.__clienti.values():
            if len(client.get_nume()) > 0:
                print(client)