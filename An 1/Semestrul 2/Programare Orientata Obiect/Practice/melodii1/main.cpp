#include <QApplication>
#include <vector>
#include <string>
#include "GUI.h"
#include "service.h"
#include "repo.h"
#include "teste.h"

using std::vector;
using std::string;

int main(int argc, char *argv[]) {
    ruleaza_toate_testele();
    QApplication app(argc, argv);
    Repo repo;
    Service service{ repo };
    GUI gui(service);
    gui.show();


    return app.exec();
}
