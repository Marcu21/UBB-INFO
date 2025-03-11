from consola.ui import UI
from domain.pacient import Pacient
from domain.internare import Internare
from persistenta.RepositoryInternari import *
from persistenta.RepositoryPacienti import *
from business.service import ServicePacienti
from business.service import ServiceInternari

repo_internari = RepoInternari()
file_repo_internari = FileRepoInternari("internari.txt")

repo_pacienti = RepoPacienti()
file_repo_pacienti = FileRepoPacienti("pacienti.txt")

service_pacienti = ServicePacienti(repo_pacienti, file_repo_pacienti)
service_internari = ServiceInternari(repo_internari, file_repo_internari)
ui = UI(service_pacienti, service_internari)

ui.run_ui()