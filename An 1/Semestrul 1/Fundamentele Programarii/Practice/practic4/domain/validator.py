from domain.emisiuni import *

class ValidatorEmisiune:
    def valideaza_emisiune(self,emisiune):
        erori = ""
        if emisiune.get_nume() == "":
            erori += "nume invalid!\n"
        if emisiune.get_tip() == "":
            erori += "tip invalid!\n"
        if int(emisiune.get_durata()) < 0:
            erori += "durata invalida!\n"
        if emisiune.get_descriere() == "":
            erori += "descriere invalida!\n"
        if len(erori)>0:
            raise ValueError(erori)