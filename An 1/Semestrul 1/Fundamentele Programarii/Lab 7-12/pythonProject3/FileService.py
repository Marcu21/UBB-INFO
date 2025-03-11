from FileRepository import *
from Domain import *
from sortari import *
import random
import string
repo_filme = FileFilmRepository()
repo_clienti = FileClientRepository()

class FileFilmService:
    def __init__(self, repo_filme, validator_film):
        self.__repo_filme = repo_filme
        self.__validator_film = validator_film

    def adauga_film(self, id_film, titlu, descriere, gen):
        film = Film(id_film, titlu, descriere, gen)
        try:
            self.__validator_film.valideaza_film(film)
            self.__repo_filme.adaugare_film(film)
            self.__repo_filme.salvare_in_fisier()
        except Exception as ex:
            print(ex)


    def get_all_filme(self):
        return self.__repo_filme.get_all()

    def cautare_film_id(self,id):
        film = self.__repo_filme.get_film(int(id))
        return film

    def cautare_film_titlu(self, titlu):
        lista_filme = []
        for film in self.__repo_filme.get_all():
            if titlu == film.get_titlu():
                lista_filme.append(film)
        return lista_filme

    """""
    def cautare_film_descriere(self, descriere):
        lista_filme = []
        for film in self.__repo_filme.get_all():
            if descriere == film.get_descriere():
                lista_filme.append(film)
        return lista_filme
    
    """""

    def cautare_film_descriere_recursiv(self, lista_filme, descriere, index=0):
        if index == len(lista_filme):
            return []

        film = lista_filme[index]
        restu = self.cautare_film_descriere_recursiv(lista_filme, descriere, index + 1)

        if descriere == film.get_descriere():
            return [film]
        else:
            return restu

    def cautare_film_descriere(self, descriere):
        lista_filme = self.__repo_filme.get_all()
        return self.cautare_film_descriere_recursiv(lista_filme, descriere)

    """"
    def cautare_film_gen(self, gen):
        lista_filme = []
        for film in self.__repo_filme.get_all():
            if gen == film.get_gen():
                lista_filme.append(film)
        return lista_filme
    """""

    def cautare_film_gen_recursiv(self, lista_filme, gen, index=0):
        if index == len(lista_filme):
            return []

        film = lista_filme[index]
        restu = self.cautare_film_gen_recursiv(lista_filme, gen, index + 1)

        if gen == film.get_gen():
            return [film]
        else:
            return restu

    def cautare_film_gen(self, gen):
        lista_filme = self.__repo_filme.get_all()
        return self.cautare_film_gen_recursiv(lista_filme, gen)


    def afisare_film_cautare(self, lista):
        for film in lista:
            print(film)

    def generare_aleator_filme(self, numar_entitati):
        for _ in range(numar_entitati):
            id_film = random.randint(1, 1000)
            titlu = ''.join(random.choice(string.ascii_letters) for _ in range(10))
            descriere = ''.join(random.choice(string.ascii_letters) for _ in range(50))
            gen = ''.join(random.choice(string.ascii_letters) for _ in range(10))
            film = Film(id_film, titlu, descriere, gen)
            self.__repo_filme.adaugare_film(film)

    def sortare_filme(self):
        lista_filme = self.get_all_filme()
        lista = merge_sort(lista_filme, key=lambda x: (x.get_gen(), x.get_descriere()),
                   reverse=False)
        for film in lista:
            print(film)

class FileClientService:
    def __init__(self, repo_clienti, validator_client):
        self.__repo_clienti = repo_clienti
        self.__validator_client = validator_client

    def adauga_client(self, id_client, nume, prenume, cnp):
        client = Client(id_client, nume, prenume, cnp)
        try:
            self.__validator_client.valideaza_client(client)
            self.__repo_clienti.adaugare_client(client)
            self.__repo_clienti.salvare_in_fisier()
        except Exception as ex:
            print(ex)

    def get_all_clienti(self):
        return self.__repo_clienti.get_all()


    def cautare_client_id(self, id):
        return self.__repo_clienti.get_client(int(id))

    def cautare_client_nume(self, nume):
        lista_clienti = []
        for client in self.__repo_clienti.get_all():
            if nume == client.get_nume():
                lista_clienti.append(client)
        return lista_clienti

    def cautare_client_prenume(self, prenume):
        lista_clienti = []
        for client in self.__repo_clienti.get_all():
            if prenume == client.get_prenume():
                lista_clienti.append(client)
        return lista_clienti

    def cautare_client_cnp(self, cnp):
        lista_clienti = []
        for client in self.__repo_clienti.get_all():
            if cnp == client.get_cnp():
                lista_clienti.append(client)
        return lista_clienti

    def afisare_client_cautari(self, lista):
        for client in lista:
            print(client)

    def generare_aleator_clienti(self, numar_entitati):
        for _ in range(numar_entitati):
            id_client = random.randint(1, 1000)
            nume = ''.join(random.choice(string.ascii_letters) for _ in range(8))
            prenume = ''.join(random.choice(string.ascii_letters) for _ in range(8))
            cnp = ''.join(random.choice(string.digits) for _ in range(13))
            client = Client(id_client, nume, prenume, cnp)
            self.__repo_clienti.adaugare_client(client)


class FileInchiriereFilme:
    def __init__(self, repo_filme, repo_clienti):
        self.__filme_inchiriate = []
        self.__client_inchiriere = []
        self.__repo_filme = repo_filme
        self.__repo_clienti = repo_clienti

    def inchiriere_film(self, id_client, id_film):
        id_client = int(id_client)
        id_film = int(id_film)
        ok_client = 0
        ok_film = 0
        for index in range(len(self.__filme_inchiriate)):
            film_inchiriat = self.__filme_inchiriate[index]
            if film_inchiriat[0] == id_film:
                film_inchiriat[1] += 1
                ok_film = 1
        if ok_film == 0:
            film_inchiriat = [id_film, 1]
            self.__filme_inchiriate.append(film_inchiriat)

        for index in range(len(self.__client_inchiriere)):
            client_inchiriator = self.__client_inchiriere[index]
            if client_inchiriator[0] == id_client:
                client_inchiriator[1] += 1
                ok_client = 1
        if ok_client == 0:
            client_inchiriator = [id_client, 1]
            self.__client_inchiriere.append(client_inchiriator)

    def returnare_film(self, id_client, id_film):
        for index in range(len(self.__filme_inchiriate)):
            film_inchiriat = self.__filme_inchiriate[index]
            if int(film_inchiriat[0]) == int(id_film):
                film_inchiriat[1] -= 1
        for index in range(len(self.__client_inchiriere)):
            client_inchiriator = self.__client_inchiriere[index]
            if int(client_inchiriator[0]) == int(id_client):
                client_inchiriator[1] -= 1

    def afisare_filme_inchiriate(self):
        for film_inchiriat in self.__filme_inchiriate:
            if film_inchiriat[1] > 0:
                id_film = film_inchiriat[0]
                film = self.__repo_filme.get_film(id_film)
                print(f"Film {film} \nNr inchirieri: {film_inchiriat[1]}\n ")

    def afisare_clienti_cu_filme_inchiriate(self):
        for index in range(len(self.__client_inchiriere)):
            client_inchiriator = self.__client_inchiriere[index]
            if client_inchiriator[1] > 0:
                id_client = client_inchiriator[0]
                client = self.__repo_clienti.get_client(id_client)
                print(f"Client {client} \nNr inchirieri: {client_inchiriator[1]}\n")

    def lista_clienti_filme_inchiriate(self):
        lista = []
        for index in range(len(self.__client_inchiriere)):
            client_inchiriator = self.__client_inchiriere[index]
            if client_inchiriator[1] > 0:
                id_client = client_inchiriator[0]
                client = self.__repo_clienti.get_client(id_client)
                lista.append(client)
        return lista



    def lista_filme_inchiriate(self):
        lista = []
        for index in range(len(self.__filme_inchiriate)):
            film_inchiriat = self.__filme_inchiriate[index]
            if film_inchiriat[1] > 0:
                id_film = film_inchiriat[0]
                film = self.__repo_filme.get_film(id_film)
                lista.append(film)
        return lista

    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
    "(O(n)=omega(n)=)teta(n), pentru ca atat in cel mai bun caz posibil, cat si in cel mai rau, trebuie sa parcurgem intreaga lista, o singura data"

    def raport_filme_inchiriate_clienti_nume(self):
        lista_clienti_sortata_nume = merge_sort(self.__repo_clienti.get_all(), key=lambda x: x.get_nume())
        for client in lista_clienti_sortata_nume:
            id = client.get_id_client()
            for client_inchiriator in self.__client_inchiriere:
                if int(client_inchiriator[0]) == int(id) and int(client_inchiriator[1]) > 0:
                    print(f"{client}\nNr filme inchiriate: {client_inchiriator[1]}")

    def raport_filme_inchiriate_clienti_nrfilme(self):
        lista_clienti_descrescatoare_nrfilme = merge_sort(self.__client_inchiriere, key=lambda x: x[1],
                                                      reverse=True)
        for client_inchiriator in lista_clienti_descrescatoare_nrfilme:
            if int(client_inchiriator[1]) > 0:
                id = int(client_inchiriator[0])
                client = self.__repo_clienti.get_client(id)
                print(f"{client}\nNr filme inchiriate: {client_inchiriator[1]}")

    def raport_filme_inchiriate(self):
        lista_filme_inchiriate_descrescator = bingo_sort(self.__filme_inchiriate, key=lambda x: x[1],
                                                     reverse=True)
        for film_inchiriat in lista_filme_inchiriate_descrescator:
            if int(film_inchiriat[1]) > 0:
                id = int(film_inchiriat[0])
                film = self.__repo_filme.get_film(id)
            print(f"{film}\nNr inchirieri: {film_inchiriat[1]}")

    def primii_30lasuta_clienti_nrfilme(self):
        lista_clienti_descrescatoare_nrfilme = bingo_sort(self.__client_inchiriere, key=lambda x: x[1],
                                                      reverse=True)
        primii = (30 * len(self.__repo_clienti.get_all())) / 100
        contor = 0
        for client_inchiriator in lista_clienti_descrescatoare_nrfilme:
            if int(contor) < int(primii):
                id = int(client_inchiriator[0])
                client = self.__repo_clienti.get_client(id)
                print(f"{client}\nNr inchirieri: {client_inchiriator[1]}")
                contor += 1
