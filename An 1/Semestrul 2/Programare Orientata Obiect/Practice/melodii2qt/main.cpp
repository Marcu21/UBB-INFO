#include <QApplication>
#include <QPushButton>
#include "teste.h"
#include "repo.h"
#include "service.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    ruleaza_toate_testele();
    QApplication a(argc, argv);
    Repo repo{"C:\\Users\\emanu\\CLionProjects\\melodii2qt\\alt.txt"};
    Service service {repo};
    GUI gui{service};
    gui.show();
    return QApplication::exec();
}
