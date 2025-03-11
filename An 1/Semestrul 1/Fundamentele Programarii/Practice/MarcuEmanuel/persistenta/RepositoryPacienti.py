from domain.pacient import Pacient
class RepoPacienti:
    def __init__(self):
        self._pacienti = []

    def goleste_lista(self):
        "goleste lista de pacienti"
        self._pacienti = []

    def afisare_pacienti(self):
        for pacient in self._pacienti:
            print(pacient)

    def get_all_pacienti(self):
        "returneaza toti pacientii"
        return self._pacienti

class FileRepoPacienti(RepoPacienti):
    def __init__(self, file_path):
        self.__file_path = "pacienti.txt"
        self._file_pacienti = []


    def read_all(self):
        "citeste toti pacientii din fisier"
        with open(self.__file_path, "r") as f:
            self._file_pacienti.clear()
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parti = line.split(",")
                    id_pacient = parti[0]
                    nume = parti[1]
                    adresa = parti[2]
                    data_nasterii = parti[3]
                    pacient = Pacient(id_pacient, nume, adresa, data_nasterii)
                    self._file_pacienti.append(pacient)

    def get_all(self):
        return self._file_pacienti

    def get_pacient(self,id):
        for pacient in self.get_all():
            if pacient.get_id_pacient() == id:
                return pacient

    def write_all_to_file(self):
        "scrie toti pacientii in fisier"
        with open(self.__file_path, "w") as f:
            for pacient in self.get_all():
                f.write(str(pacient) + "\n")


