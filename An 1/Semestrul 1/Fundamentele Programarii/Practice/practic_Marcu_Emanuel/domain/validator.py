from domain.tractor import *
from datetime import datetime
class Validator:
    def valideaza_tractor(self, tractor):
        '''
        Valideaza un tractor
        :param tractor: tractor
        raises ValueError daca tractorul nu este valid
        :return:
        '''
        erori = ""
        if tractor.get_id() < 0:
            erori += "id invalid!\n"
        if tractor.get_denumire() == '':
            erori += "denumire invalida!\n"
        if int(tractor.get_pret()) < 0:
            erori += "pret invalid!\n"
        if tractor.get_model() == '':
            erori += "model invalid!\n"
        data = tractor.get_data()
        try:
            datetime.strptime(data, '%d.%m.%Y')
        except ValueError:
            erori += "data invalida!\n"
        if len(erori) > 0:
            raise ValueError(erori)