from domain.pacient import Pacient
from persistenta.RepositoryPacienti import *
from persistenta.RepositoryInternari import *
repo_pacienti = RepoPacienti()
file_repo_pacienti = FileRepoPacienti("pacienti.txt")
repo_internari = RepoInternari()
file_repo_internari = FileRepoInternari("participari.txt")
class ServicePacienti:
    def __init__(self, repo_pacienti, file_repo_pacienti):
        self.__repo_pacienti = repo_pacienti
        self.__file_repo_pacienti = file_repo_pacienti

    def afisare_pacienti_nume(self, nume):
        """
        returneaza pacientii cu numele respectiv
        :param nume:
        :return: pacientii cu acei nume
        """
        lista = []
        self.__file_repo_pacienti.read_all()
        for pacient in self.__file_repo_pacienti.get_all():
            if pacient.get_nume() == nume:
                lista.append(pacient)
        return lista


class ServiceInternari:
    def __init__(self, repo_internari, file_repo_internari):
        self.__repo_internari = repo_internari
        self.__file_repo_internari = file_repo_internari
        self.__nr_internari = []

    def internari_pacienti(self):
        "interneaza pacientii"
        self.__nr_internari = []
        for internare in self.__file_repo_internari.get_all():
            self.__nr_internari[internare.get_id_pacient()] += 1


    def afisare_peste_2_internari(self):
        "afiseaza pacientii cu peste 2 internari"
        lista = []
        self.__file_repo_internari.read_all()
        self.internari_pacienti()
        for id_pacient in range(len(self.__nr_internari)):
            if self.__nr_internari[id_pacient] > 2:
                pacient = self.__file_repo_internari.get_pacient(id_pacient)
                lista.append(pacient)
        return lista