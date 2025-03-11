from domain.magazin import *
class Validator:
    def valideaza_magazin(self, magazin):
        erori = ""
        if int(magazin.get_id()) < 0:
            erori += "Id invalid!\n"
        if magazin.get_denumire() == '':
            erori += "Denumire invalid!\n"
        if int(magazin.get_pret()) < 0:
            erori += "Pret invalid!\n"
        if len(erori)>0:
            raise Exception(erori)