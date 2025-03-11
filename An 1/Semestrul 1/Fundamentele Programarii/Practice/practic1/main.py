from domain.examen import *
from domain.validator import *
from persistenta.repository import *
from business.service import *
from test.teste import Teste
from console.UI import *
repo = RepositoryExamen("examen.txt")
validator = ValidatorExamen()
service = ServiceExamen(repo, validator)

Teste().ruleaza_toate_testele()
run_ui()