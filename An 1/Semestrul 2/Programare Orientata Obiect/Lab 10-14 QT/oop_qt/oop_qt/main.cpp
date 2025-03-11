#include <QApplication>
#include <vector>
#include <string>
#include "gui/locatarGUI.h"
#include "service/locatar_service.h"
#include "repository/locatar_repo.h"
#include "teste/teste.h"

using std::vector;
using std::string;

int main(int argc, char *argv[]) {
    ruleaza_toate_testele();
    QApplication app(argc, argv);
    locatar_repo repo;
    locatar_service service{ repo };
    LocatarGUI gui(service);
    gui.show();
    //NotificariGUI notificariGUI{service};
    //notificariGUI.show();

    //HistogramGUI hGui { service };
    //hGui.show();

    return app.exec();
}
