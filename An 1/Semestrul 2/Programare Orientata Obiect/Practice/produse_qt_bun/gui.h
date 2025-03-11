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
    QPushButton* btnSterge = new QPushButton{"&Sterge"};
    QPushButton* btnModifica = new QPushButton{"&Modifica"};
    QPushButton* btnCauta = new QPushButton{"&Cauta"};
    QPushButton* btnFiltrare = new QPushButton{"&Filtrare"};
    QPushButton* btnSortare = new QPushButton{"&Sortare"};
    //QPushButton* btnRaport = new QPushButton{"&Raport"};
    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;


    void initConnect(){
        QObject::connect(btnExit, &QPushButton::clicked, [&](){
            QMessageBox::information(nullptr, "Info", "Exit button clicked");
            close();
        });
        QObject::connect(btnAdauga, &QPushButton::clicked, [&](){
            auto id = txtId->text().toInt();
            auto nume = txtNume->text().toStdString();
            auto tip = txtTip->text().toStdString();
            auto pret = txtPret->text().toDouble();
            qDebug()<< "Id: "<<id<<" Nume: "<<nume<<" Tip: "<<tip<<" Pret: "<<pret;
            try {
                service.adauga(id, nume, tip, pret);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(btnSterge, &QPushButton::clicked, [&](){
            auto id = txtId->text().toInt();
            auto nume = txtNume->text().toStdString();
            try {
                service.sterge(id);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(btnModifica, &QPushButton::clicked, [&](){
            auto id = txtId->text().toInt();
            auto nume = txtNume->text().toStdString();
            auto tip = txtTip->text().toStdString();
            auto pret = txtPret->text().toDouble();
            try {
                service.modifica(id, nume, tip, pret);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(btnCauta, &QPushButton::clicked, [&](){
            auto id = txtId->text().toInt();
            try {
                auto elem = service.cauta(id);
                QMessageBox::information(nullptr, "Info", QString::fromStdString(elem.get_nume())+" "+QString::fromStdString(elem.get_tip())+" "+QString::number(elem.get_pret()));
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
        QObject::connect(btnFiltrare, &QPushButton::clicked, [&](){
            auto tip = txtTip->text().toStdString();
            auto elems = service.filtrare(tip);
            table->setRowCount(0);
            int row = 0;
            for (const auto& elem : elems) {
                table->insertRow(table->rowCount());
                table->setItem(row, 0, new QTableWidgetItem(QString::number(elem.get_id())));
                table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(elem.get_nume())));
                table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(elem.get_tip())));
                table->setItem(row, 3, new QTableWidgetItem(QString::number(elem.get_pret())));
                row++;
            }
        });
        QObject::connect(btnSortare, &QPushButton::clicked, [&](){
            auto elems = service.sortare();
            table->setRowCount(0);
            int row = 0;
            for (const auto& elem : elems) {
                table->insertRow(table->rowCount());
                table->setItem(row, 0, new QTableWidgetItem(QString::number(elem.get_id())));
                table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(elem.get_nume())));
                table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(elem.get_tip())));
                table->setItem(row, 3, new QTableWidgetItem(QString::number(elem.get_pret())));
                row++;
            }
        });
        /*QObject::connect(btnRaport, &QPushButton::clicked, [&](){
            auto raport = service.raport();
            QString msg;
            for (const auto& [tip, count] : raport) {
                msg += QString::fromStdString(tip) + ": " + QString::number(count) + "\n";
            }
            QMessageBox::information(nullptr, "Raport", msg);
        });*/

    }

    void loadData() {
        table->setRowCount(0);
        int row = 0;
        auto elems = service.get_all();
        for (const auto& elem : elems) {
            table->insertRow(table->rowCount());
            table->setItem(row, 0, new QTableWidgetItem(QString::number(elem.get_id())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(elem.get_nume())));
            table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(elem.get_tip())));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(elem.get_pret())));
            row++;
        }
    }

    void initGUI(){
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        table->setColumnCount(4);
        QStringList headers{"Id", "Nume", "Tip", "Pret"};
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        lyMain->addWidget(table);

        auto stgLy = new QVBoxLayout;
        auto formLy = new QFormLayout;
        formLy->addRow("Id", txtId);
        formLy->addRow("Nume", txtNume);
        formLy->addRow("Tip", txtTip);
        formLy->addRow("Pret", txtPret);
        stgLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdauga);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnCauta);
        lyBtn->addWidget(btnFiltrare);
        lyBtn->addWidget(btnSortare);
        //lyBtn->addWidget(btnRaport);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
    }
};