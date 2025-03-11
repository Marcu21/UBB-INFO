from teste import teste
from UI import *
from UI2 import *
if __name__ == "__main__":
    teste()
    print("1. Meniu cu optiuni")
    print("2. Meniu batch mode")
    optiune = input("Alege meniul dorit: ")
    if optiune == "1":
        run_ui()
    elif optiune == "2":
        run_ui2()
    else:
        print("Optiune invalida")

