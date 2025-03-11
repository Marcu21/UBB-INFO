#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <qlineedit.h>
#include <QListWidget>
#include <qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include <string>
#include <QTableWidget>
#include "../service/locatar_service.h"
#include "../validators/exception.h"
#include <QHeaderView>
#include "notificariGUI.h"
#include "CosReadOnlyGUI.h"
#include "LocatarTableModel.h"

using std::vector;
using std::string;

class LocatarGUI : public QWidget {
    locatar_service& service;
    QVBoxLayout* dynamicButtonsLayout = new QVBoxLayout;
    TableModel* modelTabel;
    QTableView* tbl = new QTableView;
public:
    LocatarGUI(locatar_service& service) : service{ service } {
        modelTabel = new TableModel{ service.get_all() };
        tbl->setModel(modelTabel);
        initGUI();
        loadData();
        initConnect();
        initDynamicButtons();
    }

private:
    //QTableWidget* table = new QTableWidget;
    //QListWidget* lst = new QListWidget;
    QPushButton* btnExit= new QPushButton{"&Exit"};
    QPushButton* btnAdd = new QPushButton{"&Adauga"};
    QPushButton* btnSterge = new QPushButton{"&Sterge"};
    QPushButton* btnModifica = new QPushButton{"&Modifica"};
    QPushButton* btnCauta = new QPushButton{"&Cauta"};
    QPushButton* btnFiltrareTip = new QPushButton{"&Filtrare tip"};
    QPushButton* btnFiltrareSuprafata = new QPushButton{"&Filtrare suprafata"};
    QPushButton* btnSortareNumeProprietar = new QPushButton{"&Sortare nume proprietar"};
    QPushButton* btnSortareSuprafata = new QPushButton{"&Sortare suprafata"};
    QPushButton* btnSortareTipSuprafata = new QPushButton{"&Sortare tip suprafata"};
    QPushButton* btnRaport = new QPushButton{"&Raport"};
    QPushButton* btnUndo = new QPushButton{"&Undo"};
    QPushButton* btnCosCrud = new QPushButton{"&Cos CRUD"};
    QPushButton* btnCosRead = new QPushButton{"&Cos READ"};
    QLineEdit* txtApartament = new QLineEdit;
    QLineEdit* txtNumeProprietar = new QLineEdit;
    QLineEdit* txtSuprafata = new QLineEdit;
    QLineEdit* txtTipApartament = new QLineEdit;

    void initDynamicButtons() {
        //Initializeaza butoanele dinamice
        QLayoutItem* child;
        while ((child = dynamicButtonsLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        auto types = service.getUniqueTypes();
        for (const auto& type : types) {
            QPushButton* btnType = new QPushButton{QString::fromStdString(type)};
            dynamicButtonsLayout->addWidget(btnType);
            QObject::connect(btnType, &QPushButton::clicked, [this, type]() {
                auto count = service.countByType(type);
                QMessageBox::information(this, "Numar apartamente", "Numar de apartamente de tip " + QString::fromStdString(type) + ": " + QString::number(count));
            });
        }
    }

    void initConnect(){
        // Conecteaza butoanele la functiile lor
        QObject::connect(btnExit, &QPushButton::clicked, [&](){
            qDebug() << "Exit button clicked!!!!";
            QMessageBox::information(nullptr, "Info", "Exit button clicked");
            close();
        });
        QObject::connect(btnAdd, &QPushButton::clicked, [&](){
            int apartament = txtApartament->text().toInt();
            std::string numeProprietar = txtNumeProprietar->text().toStdString();
            int suprafata = txtSuprafata->text().toInt();
            std::string tipApartament = txtTipApartament->text().toStdString();
            qDebug() << "Apartament: " << apartament << " Nume proprietar: " << numeProprietar << " Suprafata: " << suprafata << " Tip apartament: " << tipApartament;
            try {
                service.add(apartament, numeProprietar, suprafata, tipApartament);
                Locatar l;
                l = Locatar::creeaza_locatar(l, apartament, numeProprietar, suprafata, tipApartament);
                modelTabel->addLocatar(l);
                loadData();
            } catch (const std::exception& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            catch(repo_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
            catch(validator_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
        });
        QObject::connect(btnSterge, &QPushButton::clicked, [&](){
            int apartament = txtApartament->text().toInt();
            std::string numeProprietar = txtNumeProprietar->text().toStdString();
            try {
                service.sterge(apartament, numeProprietar);
                loadData();
            } catch (const std::exception& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            catch(repo_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
            catch(validator_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
        });
        QObject::connect(btnModifica, &QPushButton::clicked, [&](){
            int apartament = txtApartament->text().toInt();
            std::string numeProprietar = txtNumeProprietar->text().toStdString();
            int suprafata = txtSuprafata->text().toInt();
            std::string tipApartament = txtTipApartament->text().toStdString();
            try {
                service.modifica(apartament, numeProprietar, suprafata, tipApartament);
                loadData();
            } catch (const std::exception& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            catch(repo_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
            catch(validator_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
        });
        QObject::connect(btnCauta, &QPushButton::clicked, [&](){
            int apartament = txtApartament->text().toInt();
            try {
                Locatar locatar = service.cauta(apartament);
                QMessageBox::information(nullptr, "Info", QString::fromStdString(locatar.get_nume_proprietar()));
            } catch (const std::exception& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            catch(repo_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
            catch(validator_exception& ex){
                QMessageBox::warning(nullptr, "Warning", ex.get_msg().c_str());
            }
        });

        QObject::connect(btnFiltrareTip, &QPushButton::clicked, [&](){
            std::string tipApartament = txtTipApartament->text().toStdString();
            std::vector<Locatar> locatari = service.filtrare_tip(tipApartament);
            modelTabel->setLocatari(locatari);
        });
        QObject::connect(btnFiltrareSuprafata, &QPushButton::clicked, [&](){
            int suprafata = txtSuprafata->text().toInt();
            std::vector<Locatar> locatari = service.filtrare_suprafata(suprafata);
            modelTabel->setLocatari(locatari);
        });
        QObject::connect(btnSortareNumeProprietar, &QPushButton::clicked, [&](){
            std::vector<Locatar> locatari = service.sortare_nume_proprietar();
            modelTabel->setLocatari(locatari);
        });
        QObject::connect(btnSortareSuprafata, &QPushButton::clicked, [&](){
            std::vector<Locatar> locatari = service.sortare_suprafata();
            modelTabel->setLocatari(locatari);
        });
        QObject::connect(btnSortareTipSuprafata, &QPushButton::clicked, [&](){
            std::vector<Locatar> locatari = service.sortare_tip_suprafata();
            modelTabel->setLocatari(locatari);
        });

        QObject::connect(btnRaport, &QPushButton::clicked, [&](){
            std::map<std::string, int> raport = service.raport_tip_apartament();
            QString msg;
            for (const auto& [tip, count] : raport) {
                msg += QString::fromStdString(tip) + ": " + QString::number(count) + "\n";
            }
            QMessageBox::information(nullptr, "Raport", msg);
        });
        QObject::connect(btnUndo, &QPushButton::clicked, [&](){
            try {
                service.undo();
                loadData();
            } catch (const std::exception& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
        QObject::connect(btnCosCrud, &QPushButton::clicked, [&](){
            auto crud = new NotificariGUI { service };
            crud->show();
        });
        QObject::connect(btnCosRead, &QPushButton::clicked, [&](){
            auto read = new HistogramGUI { service };
            read->show();
        });
    }


    void loadData() {
        auto allLocatar = service.get_all();
        modelTabel->setLocatari(allLocatar);
        initDynamicButtons();
    }


    /*void initGUI(){
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        lyMain->addWidget(lst);

        auto stgLy = new QVBoxLayout;
        auto formLy = new QFormLayout;
        formLy->addRow("Apartament", txtApartament);
        formLy->addRow("Nume proprietar", txtNumeProprietar);
        formLy->addRow("Suprafata", txtSuprafata);
        formLy->addRow("Tip apartament", txtTipApartament);
        stgLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdd);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnCauta);
        lyBtn->addWidget(btnFiltrareTip);
        lyBtn->addWidget(btnFiltrareSuprafata);
        lyBtn->addWidget(btnSortareNumeProprietar);
        lyBtn->addWidget(btnSortareSuprafata);
        lyBtn->addWidget(btnSortareTipSuprafata);
        lyBtn->addWidget(btnRaport);
        lyBtn->addWidget(btnUndo);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
        lyMain->addLayout(dynamicButtonsLayout);
    }*/

    void initGUI() {
        QHBoxLayout *lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        tbl->setModel(modelTabel);
        tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        lyMain->addWidget(tbl);

        auto formLy = new QFormLayout;
        formLy->addRow("Apartament", txtApartament);
        formLy->addRow("Nume proprietar", txtNumeProprietar);
        formLy->addRow("Suprafata", txtSuprafata);
        formLy->addRow("Tip apartament", txtTipApartament);
        lyMain->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdd);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnCauta);
        lyBtn->addWidget(btnFiltrareTip);
        lyBtn->addWidget(btnFiltrareSuprafata);
        lyBtn->addWidget(btnSortareNumeProprietar);
        lyBtn->addWidget(btnSortareSuprafata);
        lyBtn->addWidget(btnSortareTipSuprafata);
        lyBtn->addWidget(btnRaport);
        lyBtn->addWidget(btnUndo);
        lyBtn->addWidget(btnCosCrud);
        lyBtn->addWidget(btnCosRead);
        lyMain->addLayout(lyBtn);
        lyMain->addLayout(dynamicButtonsLayout);
    }
};