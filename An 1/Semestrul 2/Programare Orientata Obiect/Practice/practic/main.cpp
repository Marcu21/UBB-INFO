#include <QApplication>
#include "gui.h"
#include "service.h"
#include "validator.h"
#include "repo.h"
#include "teste.h"

int main(int argc, char *argv[]) {
    ruleaza_toate_testele();
    QApplication a(argc, argv);
    Repo repo;
    Validator validator;
    Service service(repo, validator);
    GUI gui(service);
    gui.show();
    return QApplication::exec();
}
