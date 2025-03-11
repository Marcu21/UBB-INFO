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

def run_ui():
        # unittest.main()
        while True:
            print("1. Adauga")
            print("2. Sterge")
            print("3. Modifica")
            print("4. Cautare")
            print("5. Inchiriere/Returnare")
            print("6. Rapoarte")
            print("7. Afisare")
            print("8. Generare aleatorie entitati")
            print("9. Exit")
            choice = input("Alege optiunea ta: ")

            if choice == "1":
                print("1. Adauga film")
                print("2. Adauga client")
                choice = input("Alege optiunea ta: ")
                if choice == "1":
                    id_film = input("Introdu id-ul filmului: ")
                    titlu = input("Introdu titlul filmului: ")
                    descriere = input("Introdu descrierea filmului: ")
                    gen = input("Introdu genul filmului: ")
                    film_service.adauga_film(id_film, titlu, descriere, gen)
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
                    gen_nou = input("Introdu genul nou al filmului: ")
                    repo_filme.modifica_film(id_film, id_film_nou, titlu_nou, descriere_nou, gen_nou)
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
                print("1. Generare filme")
                print("2. Generare client")
                choice = input("Alege optiunea ta: ")
                if choice == "1":
                    numar_entitati = int(input("Introdu numarul entitatilor care urmeaza sa fie generate: "))
                    film_service.generare_aleator_filme(numar_entitati)
                elif choice == "2":
                    numar_entitati = int(input("Introdu numarul entitatilor care urmeaza sa fie generate: "))
                    client_service.generare_aleator_clienti(numar_entitati)
                else:
                    print("Optiune invalida")

            elif choice == "9":
                break

            else:
                print("Optiune invalida")