import os
from Domain import *

class FileFilmRepository:
    def __init__(self, file_name="filme.txt"):
        self.__filme = {}
        self.__file_name = file_name
        self.incarca_date()

    def incarca_date(self):
        if not os.path.exists(self.__file_name):
            return

        with open(self.__file_name, 'r') as file:
            for line in file:
                id_film = line.strip()
                titlu = next(file).strip()
                descriere = next(file).strip()
                gen = next(file).strip()
                film = Film(id_film, titlu, descriere, gen)
                self.__filme[id_film] = film

    def salvare_in_fisier(self):
        print("Salvare in fisier...")
        with open(self.__file_name, 'w') as file:
            for film in self.get_all():
                file.write(f"{film.get_id_film()}\n{film.get_titlu()}\n{film.get_descriere()}\n{film.get_gen()}\n")

    def get_film(self, id):
        return self.__filme.get(str(id))

    def adaugare_film(self, film):
        id_film = film.get_id_film()
        if str(id_film) in self.__filme:
            raise Exception("ID existent!\n")
        self.__filme[str(id_film)] = film
        self.salvare_in_fisier()

    def stergere_film(self, id):
        self.__filme.pop(str(id))
        self.salvare_in_fisier()

    def modifica_film(self, id, id_nou, titlu_nou, descriere_noua, gen_nou):
        film = self.get_film(id)
        if film:
            film.set_id_film(id_nou)
            film.set_titlu(titlu_nou)
            film.set_descriere(descriere_noua)
            film.set_gen(gen_nou)
            self.salvare_in_fisier()

    def get_all(self):
        return list(self.__filme.values())

    def afisare_filme(self):
        for film in self.__filme.values():
            if len(film.get_titlu()) > 0:
                print(film)


class FileClientRepository:
    def __init__(self, file_name="clienti.txt"):
        self.__clienti = {}
        self.__file_name = file_name
        self.incarca_date()

    def incarca_date(self):
        if not os.path.exists(self.__file_name):
            return

        with open(self.__file_name, 'r') as file:
            for line in file:
                id_client, nume, prenume, cnp = line.strip().split('|')
                client = Client(id_client, nume, prenume, cnp)
                self.__clienti[id_client] = client

    def salvare_in_fisier(self):
        with open(self.__file_name, 'w') as file:
            for client in self.get_all():
                file.write(f"{client.get_id_client()}|{client.get_nume()}|{client.get_prenume()}|{client.get_cnp()}\n")

    def get_client(self, id):
        return self.__clienti.get(str(id))

    def adaugare_client(self, client):
        id_client = client.get_id_client()
        self.__clienti[str(id_client)] = client
        self.salvare_in_fisier()

    def stergere_client(self, id):
        self.__clienti.pop(str(id))
        self.salvare_in_fisier()

    def modifica_client(self, id, id_nou, nume_nou, prenume_nou, cnp_nou):
        client = self.get_client(id)
        if client:
            client.set_id_client(id_nou)
            client.set_nume(nume_nou)
            client.set_prenume(prenume_nou)
            client.set_cnp(cnp_nou)
            self.salvare_in_fisier()

    def get_all(self):
        return list(self.__clienti.values())

    def afisare_clienti(self):
        for client in self.__clienti.values():
            if len(client.get_nume()) > 0:
                print(client)
