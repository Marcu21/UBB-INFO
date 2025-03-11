#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <qlineedit.h>
#include <QTableWidget>
#include <qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include <string>
#include "service.h"
#include <stdexcept>
#include <QHeaderView>

using std::vector;
using std::string;

class GUI : public QWidget {
    Service& service;
public:
    GUI(Service& service) :service{ service } {
        initGUI();
        loadData();
        initConnect();
    }
private:
    QTableWidget* table = new QTableWidget;
    QPushButton* btnExit= new QPushButton{"&Exit"};
    QPushButton* btnAdauga = new QPushButton{"&Adauga"};
    QPushButton* btnCauta = new QPushButton{"&Cauta"};
    QPushButton* btnSortarePret = new QPushButton{"&Sortare pret"};
    QPushButton* btnSortareNumar = new QPushButton{"&Sortare numar"};
    QPushButton* btnNesortat = new QPushButton{"&Nesortat"};
    QPushButton* btnRaport = new QPushButton{"&Raport"};
    QPushButton* btnCumparare = new QPushButton{"&Cumparare"};
    QLineEdit* txtCod = new QLineEdit;
    QLineEdit* txtDenumire = new QLineEdit;
    QLineEdit* txtNumar = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;


    void initConnect(){
        //Conecteaza butoanele la GUI
        QObject::connect(btnExit, &QPushButton::clicked, [&](){
            QMessageBox::information(nullptr, "Info", "Exit button clicked");
            close();
        });
        QObject::connect(btnAdauga, &QPushButton::clicked, [&](){
            auto cod = txtCod->text().toInt();
            auto denumire = txtDenumire->text().toStdString();
            auto numar = txtNumar->text().toInt();
            auto pret = txtPret->text().toDouble();
            qDebug()<< "Cod: "<<cod<<" Denumire: "<<denumire<<" Numar: "<<numar<<" Pret: "<<pret;
            try {
                service.adauga(cod, denumire, numar, pret);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(btnCauta, &QPushButton::clicked, [&](){
            auto cod = txtCod->text().toInt();
            try {
                auto elem = service.cauta(cod);
                QMessageBox::information(nullptr, "Info", QString::fromStdString(elem.get_denumire())+" "+QString::number(elem.get_numar())+" "+QString::number(elem.get_pret()));
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
        QObject::connect(btnSortarePret, &QPushButton::clicked, [&](){
            auto elems = service.sortare_pret();
            table->setRowCount(0);
            int row = 0;
            for (const auto& elem : elems) {
                table->insertRow(table->rowCount());
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(elem.get_denumire())));
                table->setItem(row, 1, new QTableWidgetItem(QString::number(elem.get_pret())));
                row++;
            }
        });
        QObject::connect(btnSortareNumar, &QPushButton::clicked, [&](){
            vector<Produs> elems = service.sortare_numar();
            table->setRowCount(0);
            int row = 0;
            for (const auto& elem : elems) {
                table->insertRow(table->rowCount());
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(elem.get_denumire())));
                table->setItem(row, 1, new QTableWidgetItem(QString::number(elem.get_pret())));
                row++;
            }
        });
        QObject::connect(btnNesortat, &QPushButton::clicked, [&](){
            auto elems = service.get_all();
            table->setRowCount(0);
            int row = 0;
            for (const auto& elem : elems) {
                table->insertRow(table->rowCount());
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(elem.get_denumire())));
                table->setItem(row, 1, new QTableWidgetItem(QString::number(elem.get_pret())));
                row++;
            }
        });
        QObject::connect(btnRaport, &QPushButton::clicked, [&](){
            int cod = txtCod->text().toInt();
            try {
                int count = service.raport(cod);
                QString msg;
                msg += QString::number(cod) + ": " + QString::number(count) + "\n";
                QMessageBox::information(nullptr, "Raport", msg);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
        QObject::connect(btnCumparare, &QPushButton::clicked, [&](){
            auto cod = txtCod->text().toInt();
            try {
                service.cumparare(cod);
                Produs elem = service.cauta(cod);
                QMessageBox::information(nullptr, "Element cumparat!", QString::fromStdString(elem.get_denumire())+" "+QString::number(elem.get_numar())+" "+QString::number(elem.get_pret()));
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
    }

    void loadData() {
        //Incarca datele in tabel
        table->setRowCount(0);
        int row = 0;
        auto elems = service.get_all();
        for (const auto& elem : elems) {
            table->insertRow(table->rowCount());
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(elem.get_denumire())));
            table->setItem(row, 1, new QTableWidgetItem(QString::number(elem.get_pret())));
            row++;
        }
    }

    void initGUI(){
        //Initializeaza GUI-ul
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        table->setColumnCount(2);
        QStringList headers{"Denumire", "Pret"};
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        lyMain->addWidget(table);

        auto stgLy = new QVBoxLayout;
        auto formLy = new QFormLayout;
        formLy->addRow("Cod", txtCod);
        formLy->addRow("Denumire", txtDenumire);
        formLy->addRow("Numar", txtNumar);
        formLy->addRow("Pret", txtPret);
        stgLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdauga);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnCauta);
        lyBtn->addWidget(btnSortarePret);
        lyBtn->addWidget(btnSortareNumar);
        lyBtn->addWidget(btnNesortat);
        lyBtn->addWidget(btnRaport);
        lyBtn->addWidget(btnCumparare);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
    }
};
