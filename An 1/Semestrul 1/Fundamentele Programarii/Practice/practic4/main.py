from teste.test import *
from domain.emisiuni import *
from domain.validator import *
from persistenta.repository import *
from business.service import *
from console.UI import *
validator = ValidatorEmisiune()
repo = RepositoryEmisiuni("emisiuni.txt")
service = ServiceEmisiuni(repo, validator)

test = Teste()

test.ruleaza_toate_testele()
run_ui()