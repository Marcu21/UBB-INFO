from domain.examen import *
from domain.validator import *
from persistenta.repository import *
from business.service import *
repo = RepositoryExamen("examen.txt")
validator = ValidatorExamen()
service = ServiceExamen(repo, validator)
def run_ui():
    lista = service.examene_ziua_urmatoare()
    if len(lista) == 0:
        print("Nu sunt examene programate pe maine")
    else:
        print("Examenele de maine sunt urmatoarele:")
        for examen in lista:
            print(examen)

    while True:
        print("1. Adaugare")
        print("2. Examene programate in urmatoarele 3 zile")
        print("3. Export in fisier")
        choice = input("Alege optiunea ta")

        if choice == "1":
            data = input("Introdu data: ")
            ora = input("Introdu ora: ")
            materia = input("Introdu materia: ")
            sesiune = input("Introdu sesiunea(normala/restanta): ")
            try:
                service.adaugare(data, ora, materia, sesiune)
            except Exception as ve:
                print(ve)

        elif choice == "2":
            data = input("Introdu data: ")
            lista = service.examene_3_zile(data)
            if len(lista) == 0:
                print("Nu sunt programate examene pe urmatoarele 3 zile.")
            else:
                print("Examenele din urmtoarele 3 zile sunt: ")
                for examen in lista:
                    print(examen)

        elif choice == "3":
            nume_fisier = input("Introdu numele fisierului: ")
            sir = input("Introdu sirul care sa se regaseasca in materie")
            service.export_examene_fisier(nume_fisier, sir)

        else:
            break