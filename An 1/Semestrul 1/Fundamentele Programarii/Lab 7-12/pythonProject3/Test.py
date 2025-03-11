from Domain import *
from Service import *
from Repository import *
from Validator import *

repo_filme = FilmRepository()
validator_film = ValidatorFilm()
film_service = FilmService(repo_filme, validator_film)

repo_clienti = ClientRepository()
validator_client = ValidatorClienti()
client_service = ClientService(repo_clienti, validator_client)

inchiriere_filme = InchiriereFilme(repo_filme, repo_clienti)


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
