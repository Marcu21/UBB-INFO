class Film:
    def __init__(self, id_film, titlu, descriere):  # gen
        self.__id_film = id_film
        self.__titlu = titlu
        self.__descriere = descriere
        # self.__gen = gen

    def get_id_film(self):
        return self.__id_film

    def get_titlu(self):
        return self.__titlu

    def get_descriere(self):
        return self.__descriere

    # def get_gen(self):
    #    return self.__gen

    def set_id_film(self, id_nou):
        self.__id_film = id_nou

    def set_titlu(self, titlu_nou):
        self.__titlu = titlu_nou

    def set_descriere(self, descriere_noua):
        self.__descriere = descriere_noua

    # def set_gen(self, gen_nou):
    #    self.__gen = gen_nou

    def __str__(self):
        return f"[{self.__id_film}]{self.__titlu}: {self.__descriere}| "  # {self.__gen


class ValidatorFilm:
    def valideaza_film(self, film):
        erori = ""
        if int(film.get_id_film()) < 0:
            erori += "id invalid!\n"
        if film.get_titlu() == "":
            erori += "titlu invalid!\n"
        if film.get_descriere() == "":
            erori += "descriere invalida!\n"
        # if film.get_gen() == "":
        #    erori += "gen invalid!\n"
        if len(erori) > 0:
            raise Exception(erori)


class FilmRepository:
    def __init__(self):
        self.__filme = {}

    def get_film(self, id):
        return self.__filme.get(id)

    def adaugare_film(self, film):
        id_film = film.get_id_film()
        if id_film in self.__filme:
            raise Exception("id existent!\n")
        self.__filme[id_film] = film

    def stergere_film(self, id):
        self.__filme.pop(id)

    def modifica_film(self, id, id_nou, titlu_nou, descriere_noua):  # gen_nou
        film = self.get_film(id)
        film.set_id_film(id_nou)
        film.set_titlu(titlu_nou)
        film.set_descriere(descriere_noua)
        # film.set_gen(gen_nou)

    def get_all(self):
        return [self.__filme[x] for x in self.__filme.keys()]

    def afisare_filme(self):
        for film in self.__filme.values():
            if len(film.get_titlu()) > 0:
                print(film)


class FilmService:
    def __init__(self, repo_filme, validator_film):
        self.__repo_filme = repo_filme
        self.__validator_film = validator_film

    def adauga_film(self, id_film, titlu, descriere):  # gen
        film = Film(id_film, titlu, descriere)  # gen
        self.__validator_film.valideaza_film(film)
        self.__repo_filme.adaugare_film(film)

    def get_all_filme(self):
        return self.__repo_filme.get_all()

    def cautare_film_id(self, id):
        film = self.__repo_filme.get_film(id)
        return film

    def cautare_film_titlu(self, titlu):
        lista_filme = []
        for film in self.__repo_filme.get_all():
            if titlu == film.get_titlu():
                lista_filme.append(film)
        return lista_filme

    def cautare_film_descriere(self, descriere):
        lista_filme = []
        for film in self.__repo_filme.get_all():
            if descriere == film.get_descriere():
                lista_filme.append(film)
        return lista_filme

    def cautare_film_gen(self, gen):
        lista_filme = []
        for film in self.__repo_filme.get_all():
            if gen == film.get_gen():
                lista_filme.append(film)
        return lista_filme

    def afisare_film_cautare(self, lista):
        for film in lista:
            print(film)



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


class ValidatorClienti:
    def valideaza_client(self, client):
        erori = ""
        if int(client.get_id_client()) < 0:
            erori += "id invalid!\n"
        if client.get_nume() == "":
            erori += "nume invalid!\n"
        if client.get_prenume() == "":
            erori += "prenume invalid!\n"
        if int(len(client.get_cnp())) != 13:
            erori += "cnp invalid!\n"
        if len(erori) > 0:
            raise Exception(erori)


class ClientRepository:
    def __init__(self):
        self.__clienti = {}

    def get_client(self, id):
        return self.__clienti.get(id)

    def adaugare_client(self, client):
        id_client = client.get_id_client()
        if id_client in self.__clienti:
            raise Exception("id existent!\n")
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


class ClientService:
    def __init__(self, repo_clienti, validator_client):
        self.__repo_clienti = repo_clienti
        self.__validator_client = validator_client

    def adauga_client(self, id_client, nume, prenume, cnp):
        client = Client(id_client, nume, prenume, cnp)
        self.__validator_client.valideaza_client(client)
        self.__repo_clienti.adaugare_client(client)

    def get_all_clienti(self):
        return self.__repo_clienti.get_all()

    def cautare_client_id(self, id):
        return self.__repo_clienti.get_client(id)

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


class InchiriereFilme:
    def __init__(self, repo_filme, repo_clienti):
        self.__filme_inchiriate = {}
        self.__client_inchiriere = {}
        self.__repo_filme = repo_filme
        self.__repo_clienti = repo_clienti

    def inchiriere_film(self, id_client, id_film):
        id_client = int(id_client)
        id_film = int(id_film)
        if id_film not in self.__filme_inchiriate:
            self.__filme_inchiriate[id_film] = 0
        self.__filme_inchiriate[id_film] += 1
        if id_client not in self.__client_inchiriere:
            self.__client_inchiriere[id_client] = 0
        self.__client_inchiriere[id_client] += 1

    def returnare_film(self, id_client, id_film):
        self.__filme_inchiriate[id_film] -= 1
        self.__client_inchiriere[id_client] -= 1

    def afisare_filme_inchiriate(self):
        for film_id, numar_inchirieri in self.__filme_inchiriate.items():
            if numar_inchirieri > 0:
                film = self.__repo_filme.get_film(film_id)
                print(f"Film ID: {film_id}, Titlu: {film.get_titlu()}, Inchirieri: {numar_inchirieri}")

    def afisare_clienti_cu_filme_inchiriate(self):
        for index in range(len(self.__client_inchiriere)):
            if (self.__client_inchiriere[index] > 0):
                client = repo_clienti.get_client(index)
                print(client)

    def raport_filme_inchiriate_clienti_nume(self):
        lista_clienti_sortata_nume = sorted(self.__repo_clienti, key=lambda x: x.nume)
        for client in lista_clienti_sortata_nume:
            if int(self.__client_inchiriere(client.get_id_client())) > 0:
                print(
                    f"{self.__repo_clienti[client.get_id_client()]}\nNr filme inchiriate: {self.__client_inchiriere(client.get_id_client())}")

    def raport_filme_inchiriate_clienti_nrfilme(self):
        lista_clienti_descrescatoare_nrfilme = sorted(enumerate(self.__client_inchiriere), key=lambda x: x[1],
                                                      reverse=True)
        for index, valoare in lista_clienti_descrescatoare_nrfilme:
            print(f"{self.__repo_clienti[index]}\nNr filme inchiriate: {valoare}")

    def raport_filme_inchiriate(self):
        lista_filme_inchiriate_descrescator = sorted(enumerate(self.__filme_inchiriate), key=lambda x: x[1],
                                                     reverse=True)
        for index, valoare in lista_filme_inchiriate_descrescator:
            print(f"{self.__repo_filme[index]}\nNr inchirieri: {valoare}")

    def primii_30lasuta_clienti_nrfilme(self):
        lista_clienti_descrescatoare_nrfilme = sorted(enumerate(self.__client_inchiriere.items()), key=lambda x: x[1],
                                                      reverse=True)
        primii = (30 * int(len(self.__repo_clienti))) / 100
        contor = 0
        for index, valoare in lista_clienti_descrescatoare_nrfilme and int(contor) < int(primii):
            print(f"{self.__repo_filme[index]}\nNr inchirieri: {valoare}")
            contor += 1


import unittest


class TestFilmService(unittest.TestCase):
    def setUp(self):
        self.repo_filme = FilmRepository()
        self.validator_film = ValidatorFilm()
        self.film_service = FilmService(self.repo_filme, self.validator_film)

    def test_adauga_film(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        filme = self.film_service.get_all_filme()
        self.assertEqual(len(filme), 1)
        self.assertEqual(filme[0].get_titlu(), "Inception")
        self.assertEqual(filme[0].get_descriere(), "Mind-bending thriller")
        self.assertEqual(filme[0].get_gen(), "Sci-Fi")

    def test_modifica_film(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        self.repo_filme.modifica_film(1, 1, "Inception 2", "Even more mind-bending", "Sci-Fi")
        filme = self.film_service.get_all_filme()
        self.assertEqual(filme[0].get_titlu(), "Inception 2")
        self.assertEqual(filme[0].get_descriere(), "Even more mind-bending")
        self.assertEqual(filme[0].get_gen(), "Sci-Fi")

    def test_sterge_film(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        self.repo_filme.stergere_film(1)
        filme = self.film_service.get_all_filme()
        self.assertEqual(len(filme), 0)

    def test_cautare_film_titlu(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        rezultat = self.film_service.cautare_film_titlu("Inception")
        self.assertEqual(len(rezultat), 1)
        self.assertEqual(rezultat[0].get_titlu(), "Inception")

    def test_cautare_film_id(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        rezultat = self.film_service.cautare_film_id(1)
        self.assertIsNotNone(rezultat)
        self.assertEqual(rezultat.get_titlu(), "Inception")

    def test_cautare_film_descriere(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        rezultate = self.film_service.cautare_film_descriere("Mind-bending thriller")
        self.assertEqual(len(rezultate), 1)
        self.assertEqual(rezultate[0].get_titlu(), "Inception")

    def test_cautare_film_gen(self):
        self.film_service.adauga_film(1, "Inception", "Mind-bending thriller", "Sci-Fi")
        rezultate = self.film_service.cautare_film_gen("Sci-Fi")
        self.assertEqual(len(rezultate), 1)
        self.assertEqual(rezultate[0].get_titlu(), "Inception")


class TestClientService(unittest.TestCase):
    def setUp(self):
        self.repo_clienti = ClientRepository()
        self.validator_client = ValidatorClienti()
        self.client_service = ClientService(self.repo_clienti, self.validator_client)

    def test_adauga_client(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        clienti = self.client_service.get_all_clienti()
        self.assertEqual(len(clienti), 1)
        self.assertEqual(clienti[0].get_nume(), "John")

    def test_modifica_client(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        self.repo_clienti.modifica_client(1, 1, "Jane", "Doe", "1234567890123")
        clienti = self.client_service.get_all_clienti()
        self.assertEqual(clienti[0].get_nume(), "Jane")

    def test_sterge_client(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        self.repo_clienti.stergere_client(1)
        clienti = self.client_service.get_all_clienti()
        self.assertEqual(len(clienti), 0)

    def test_cautare_client_nume(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        rezultat = self.client_service.cautare_client_nume("John")
        self.assertEqual(len(rezultat), 1)
        self.assertEqual(rezultat[0].get_nume(), "John")

    def test_cautare_client_id(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        rezultat = self.client_service.cautare_client_id(1)
        self.assertIsNotNone(rezultat)
        self.assertEqual(rezultat.get_nume(), "John")

    def test_cautare_client_prenume(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        rezultate = self.client_service.cautare_client_prenume("Doe")
        self.assertEqual(len(rezultate), 1)
        self.assertEqual(rezultate[0].get_nume(), "John")

    def test_cautare_client_cnp(self):
        self.client_service.adauga_client(1, "John", "Doe", "1234567890123")
        rezultate = self.client_service.cautare_client_cnp("1234567890123")
        self.assertEqual(len(rezultate), 1)
        self.assertEqual(rezultate[0].get_nume(), "John")


class TestInchiriereFilme(unittest.TestCase):
    def setUp(self):
        self.repo_filme = FilmRepository()
        self.validator_film = ValidatorFilm()
        self.repo_clienti = ClientRepository()
        self.validator_client = ValidatorClienti()
        self.inchiriere_service = InchiriereFilme(self.repo_filme, self.repo_clienti)

    def test_inchiriere_si_returnare(self):
        self.repo_filme.adaugare_film(Film(1, "Inception", "Mind-bending thriller", "Sci-Fi"))
        self.repo_clienti.adaugare_client(Client(1, "John", "Doe", "1234567890123"))

        self.inchiriere_service.inchiriere_film(1, 1)
        self.assertEqual(self.inchiriere_service._InchiriereFilme__filme_inchiriate[1], 1)
        self.assertEqual(self.inchiriere_service._InchiriereFilme__client_inchiriere[1], 1)

        self.inchiriere_service.returnare_film(1, 1)
        self.assertEqual(self.inchiriere_service._InchiriereFilme__filme_inchiriate[1], 0)
        self.assertEqual(self.inchiriere_service._InchiriereFilme__client_inchiriere[1], 0)


repo_filme = FilmRepository()
validator_film = ValidatorFilm()
film_service = FilmService(repo_filme, validator_film)

repo_clienti = ClientRepository()
validator_client = ValidatorClienti()
client_service = ClientService(repo_clienti, validator_client)

inchiriere_filme = InchiriereFilme(repo_filme, repo_clienti)

if __name__ == "__main__":
    # unittest.main()
    while True:
        print("1. Adauga")
        print("2. Sterge")
        print("3. Modifica")
        print("4. Cautare")
        print("5. Inchiriere/Returnare")
        print("6. Rapoarte")
        print("7. Afisare")
        print("8. Exit")
        choice = input("Alege optiunea ta: ")

        if choice == "1":
            print("1. Adauga film")
            print("2. Adauga client")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                id_film = input("Introdu id-ul filmului: ")
                titlu = input("Introdu titlul filmului: ")
                descriere = input("Introdu descrierea filmului: ")
                # gen = input("Introdu genul filmului: ")
                film_service.adauga_film(id_film, titlu, descriere)  # gen
            elif choice == "2":
                id_client = input("Introdu id-ul clientului: ")
                nume = input("Introdu numele clientului: ")
                prenume = input("Introdu prenumele clientului: ")
                cnp = input("Introdu cnp-ul clientului: ")
                client_service.adauga_client(id_client, nume, prenume, cnp)
            else:
                print("Optiune invalida.")

        elif choice == "2":
            print("1. Sterge film")
            print("2. Sterge client")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                id_film = input("Introdu id-ul filmului: ")
                repo_filme.stergere_film(id_film)
            elif choice == "2":
                id_client = input("Introdu id-ul clientului: ")
                repo_clienti.stergere_client(id_client)
            else:
                print("Optiune invalida.")

        elif choice == "3":
            print("1. Modifica film")
            print("2. Modifica client")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                id_film = input("Introdu id-ul filmului pe care vrei sa il modifici: ")
                id_film_nou = input("Introdu id-ul nou al filmului: ")
                titlu_nou = input("Introdu titlul nou al filmului: ")
                descriere_nou = input("Introdu descrierea noua a filmului: ")
                # gen_nou = input("Introdu genul nou al filmului: ")
                repo_filme.modifica_film(id_film, id_film_nou, titlu_nou, descriere_nou)  # gen_nou
            elif choice == "2":
                id_client = input("Introdu id-ul clientului pe care vrei sa il modifici")
                id_client_nou = input("Introdu id-ul nou al clientului")
                nume_nou = input("Introdu numele nou al clientului: ")
                prenume_nou = input("Introdu prenumele nou al clientului: ")
                cnp_nou = input("Introdu cnp-ul nou al clientului: ")
                repo_clienti.modifica_client(id_client, id_client_nou, nume_nou, prenume_nou, cnp_nou)
            else:
                print("Optiune invalida.")

        elif choice == "4":
            print("1. Cautare film")
            print("2. Cautare client")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                print("1. Cautare film dupa id")
                print("2. Cautare film dupa titlu")
                print("3. Cautare film dupa descriere")
                print("4. Cautare film dupa gen")
                choice = input("Alege optiunea ta: ")
                if choice == "1":
                    id_film = input("Introdu id-ul filmului: ")
                    print(film_service.cautare_film_id(id_film))
                elif choice == "2":
                    titlu_film = input("Introdu titlul filmului: ")
                    film_service.afisare_film_cautare(film_service.cautare_film_titlu(titlu_film))
                elif choice == "3":
                    descriere_film = input("Introdu descrierea filmului: ")
                    film_service.afisare_film_cautare(film_service.cautare_film_descriere(descriere_film))
                elif choice == "4":
                    gen_film = input("Introdu genul filmului: ")
                    film_service.afisare_film_cautare(film_service.cautare_film_gen(gen_film))
                else:
                    print("Optiune invalida")
            elif choice == "2":
                print("1. Cautare client dupa id")
                print("2. Cautare client dupa nume")
                print("3. Cautare client dupa prenume")
                print("4. Cautare client dupa cnp")
                choice = input("Alege optiunea ta: ")
                if choice == "1":
                    id_client = input("Introdu id-ul clientului: ")
                    print(client_service.cautare_client_id(id_client))
                elif choice == "2":
                    nume_client = input("Introdu numele clientului: ")
                    client_service.afisare_client_cautari(client_service.cautare_client_nume(nume_client))
                elif choice == "3":
                    prenume_client = input("Introdu prenumele clientului: ")
                    client_service.afisare_client_cautari(client_service.cautare_client_prenume(prenume_client))
                elif choice == "4":
                    cnp_client = input("Introdu cnp-ul clientului: ")
                    client_service.afisare_client_cautari(client_service.cautare_client_cnp(cnp_client))
                else:
                    print("Optiune invalida")

        elif choice == "5":
            print("1. Inchiriere film")
            print("2. Returnare film")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                id_client = input("Introdu id-ul clientului care inchiriaza: ")
                id_film = input("Introdu id-ul filmului inchiriat: ")
                inchiriere_filme.inchiriere_film(id_client, id_film)
            elif choice == "2":
                id_client = input("Introdu id-ul clientului care returneaza: ")
                id_film = input("Introdu id-ul filmului returnat: ")
                inchiriere_filme.returnare_film(id_client, id_film)
            else:
                print("Optiune invalida")

        elif choice == "6":
            print("1. Clienti cu filme inchiriate ordonat dupa nume")
            print("2. Clienti cu filme inchiriate ordonat dupa numarul de filme inchiriate")
            print("3. Cele mai inchiriate filme")
            print("4. Primii 30% clienti cu cele mai multe filme")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                inchiriere_filme.raport_filme_inchiriate_clienti_nume()
            elif choice == "2":
                inchiriere_filme.raport_filme_inchiriate_clienti_nrfilme()
            elif choice == "3":
                inchiriere_filme.raport_filme_inchiriate()
            elif choice == "4":
                inchiriere_filme.primii_30lasuta_clienti_nrfilme()
            else:
                print("Optiune invalida")

        elif choice == "7":
            print("1. Afisare filme")
            print("2. Afisare clienti")
            print("3. Afisare filme inchiriate")
            print("4. Afisare clienti cu filme inchiriate")
            choice = input("Alege optiunea ta: ")
            if choice == "1":
                repo_filme.afisare_filme()
            elif choice == "2":
                repo_clienti.afisare_clienti()
            elif choice == "3":
                inchiriere_filme.afisare_filme_inchiriate()
            elif choice == "4":
                inchiriere_filme.afisare_clienti_cu_filme_inchiriate()
            else:
                print("Optiune invalida")

        elif choice == "8":
            break

        else:
            print("Optiune invalida")