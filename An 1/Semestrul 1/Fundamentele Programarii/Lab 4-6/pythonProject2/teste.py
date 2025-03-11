from TravelPackage import TravelPackage
from TravelAgency import TravelAgency
agency = TravelAgency()
def teste():
    agency = TravelAgency()

    pachet1 = TravelPackage("24.08.2023", "30.08.2023", "maiahi", 500)
    pachet2 = TravelPackage("25.08.2023", "29.08.2023", "maiahu", 600)
    pachet3 = TravelPackage("25.09.2023", "30.09.2023", "maiaha", 450)
    pachet4 = TravelPackage("01.09.2023", "10.09.2023", "maiahi", 700)
    pachet5 = TravelPackage("03.09.2023", "13.09.2023", "maiahi", 1000)
    pachet6 = TravelPackage("21.08.2023", "30.08.2023", "maiahaha", 900)

    agency.adauga_pachet(pachet1)
    agency.adauga_pachet(pachet2)
    agency.adauga_pachet(pachet3)
    agency.adauga_pachet(pachet4)
    agency.adauga_pachet(pachet5)
    agency.adauga_pachet(pachet6)

    data_inceput_verif = "23.08.2023"
    data_sfarsit_verif = "31.08.2023"

    rezultat_cautare_interval = [pachet1,pachet2]
    assert agency.cautare_interval(data_inceput_verif,  data_sfarsit_verif) == rezultat_cautare_interval

    destinatie = "maiahi"
    pret = "1000"
    rezultat_cautare_destinatie_pret = [pachet1, pachet4]
    assert agency.cautare_destinatie_pret(destinatie, pret) == rezultat_cautare_destinatie_pret

    data_sfarsit = "30.08.2023"
    rezultat_cautare_data_sfarsit = [pachet1, pachet6]
    assert agency.cautare_data_sfarsit(data_sfarsit) == rezultat_cautare_data_sfarsit

    destinatie = "maiahi"
    rezultat_raport_destinatie = [pachet1, pachet4, pachet5]
    assert agency.raport_destinatie(destinatie) == rezultat_raport_destinatie

    data_inceput = "24.08.2023"
    data_sfarsit = "30.08.2023"
    rezultat_raport_perioada = [pachet1]
    assert agency.raport_perioada(data_inceput, data_sfarsit) == rezultat_raport_perioada

    destinatie = "maiahi"
    rezultat_raport_medie_pret_destinatie = "733"
    assert agency.raport_medie_pret_destinatie(destinatie) == int(rezultat_raport_medie_pret_destinatie)

    destinatie = "maiahi"
    pret = "800"
    rezultat_filtrare_eliminare_destinatie_pret = [pachet1, pachet4]
    assert agency.filtrare_eliminare_destinatie_pret(destinatie, pret) == rezultat_filtrare_eliminare_destinatie_pret

    luna = "9"
    rezultat_filtrare_eliminare_luna = [pachet1, pachet2, pachet6]
    assert agency.filtrare_eliminare_luna(luna) == rezultat_filtrare_eliminare_luna

    destinatie = "maiahaha"
    rezultat_stergere_destinatie = [pachet1,pachet2,pachet3,pachet4,pachet5]
    assert agency.stergere_destinatie(destinatie) == rezultat_stergere_destinatie

    durata = "5"
    rezultat_stergere_durata = [pachet1,pachet3,pachet4,pachet5]
    assert agency.stergere_durata(durata) == rezultat_stergere_durata


    pret = "450"
    rezultat_stergere_pret = [pachet3]
    assert agency.stergere_pret(pret) == rezultat_stergere_pret