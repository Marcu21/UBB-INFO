from domain.tractor import *
from domain.validator import *
from persistenta.repository import *
from business.service import *
from console.UI import *
from teste.test import *
repo = RepositoryTractoare("tractoare.txt")
validator = Validator()
service = ServiceTractoare(repo, validator)
teste = Teste()
teste.ruleaza_toate_testele()
ui = UI(repo, validator, service)

ui.run_ui()

