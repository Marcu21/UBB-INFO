from UI import *
from Domain import *
from Service import *
from Repository import *
from Validator import *
from UI_file import *
from Test import *
import unittest

repo_filme = FilmRepository()
validator_film = ValidatorFilm()
film_service = FilmService(repo_filme, validator_film)

repo_clienti = ClientRepository()
validator_client = ValidatorClienti()
client_service = ClientService(repo_clienti, validator_client)

inchiriere_filme = InchiriereFilme(repo_filme, repo_clienti)

suite1 = unittest.TestLoader().loadTestsFromTestCase(TestFilmService)
suite2 = unittest.TestLoader().loadTestsFromTestCase(TestClientService)

result1 = unittest.TextTestRunner().run(suite1)
result2 = unittest.TextTestRunner().run(suite2)

if result1.wasSuccessful():
    print("Primul set de teste finalizat cu succes!")
    print("--------------------------------")
if result2.wasSuccessful():
    print("Al doilea set de teste finalizat cu succes!")
    print("--------------------------------")
else:
    print("Some tests failed.")
    exit()


while True:
    print("1. Date salvate in memorie")
    print("2. Date salvate in fisier")
    print("3. Exit")
    choice = input("Alege optiunea ta: ")
    if choice == "1":
        run_ui()

    elif choice == "2":
        run_ui_file()

    elif choice == "3":
        break

    else:
        print("Optiune invalida")