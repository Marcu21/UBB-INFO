from domain.internare import Internare
class RepoInternari:
    def __init__(self):
        self._internari = {}

    def goleste_lista_internari(self):
        "goleste lista de internari"
        self._internari = {}


    def get_all_internari(self):
        "returneaza toate internarile"
        return [self._internari[x] for x in self._internari.keys()]


class FileRepoInternari(RepoInternari):
    def __init__(self, file_path):
        self.__file_path = "participari.txt"
        RepoInternari.__init__(self)
        self.__file_internari = []

    def read_all(self):
        "citeste lista de internari"
        with open(self.__file_path, "r") as f:
            RepoInternari.goleste_lista_internari(self)
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parti = line.split(",")
                    cod_internare = parti[0]
                    id_pacient = parti[1]
                    diagnostic = parti[2]
                    data_internarii = parti[3]
                    data_externarii = parti[4]
                    internare = Internare(cod_internare, id_pacient, diagnostic, data_internarii, data_externarii)
                    self.__file_internari.append(internare)

    def get_all(self):
        return self.__file_internari

    def write_all_to_file(self):
        "scrie toate internarile in fisier"
        with open(self.__file_path, "w") as f:
            for internare in self.get_all():
                f.write(str(internare) + "\n")