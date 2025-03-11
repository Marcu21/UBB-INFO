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
    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtTitlu = new QLineEdit;
    QLineEdit* txtArtist = new QLineEdit;
    QLineEdit* txtGen = new QLineEdit;


    void initConnect(){
        QObject::connect(btnExit, &QPushButton::clicked, [&](){
            QMessageBox::information(nullptr, "Info", "Exit button clicked");
            close();
        });
        QObject::connect(btnAdauga, &QPushButton::clicked, [&](){
            auto id = txtId->text().toInt();
            auto nume = txtTitlu->text().toStdString();
            auto tip = txtArtist->text().toStdString();
            auto pret = txtGen->text().toStdString();
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
            auto nume = txtTitlu->text().toStdString();
            auto tip = txtArtist->text().toStdString();
            auto pret = txtGen->text().toStdString();
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
                QMessageBox::information(nullptr, "Info", QString::fromStdString(elem.get_titlu())+" "+QString::fromStdString(elem.get_artist())+" "+QString::fromStdString(elem.get_gen()));
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
        QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
            int row = table->currentRow();
            if (row >= 0) {
                txtId->setText(table->item(row, 0)->text());
                txtTitlu->setText(table->item(row, 1)->text());
                txtArtist->setText(table->item(row, 2)->text());
                txtGen->setText(table->item(row, 3)->text());
            }
        });
    }

    void loadData() {
        table->setRowCount(0);
        int row = 0;
        auto elems = service.sortare();
        for (const auto& elem : elems) {
            table->insertRow(table->rowCount());
            table->setItem(row, 0, new QTableWidgetItem(QString::number(elem.get_id())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(elem.get_titlu())));
            table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(elem.get_artist())));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(elem.get_gen())));
            row++;
        }
    }

    void initGUI(){
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        table->setColumnCount(4);
        QStringList headers{"Id", "Titlu", "Artist", "Gen"};
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        lyMain->addWidget(table);

        auto stgLy = new QVBoxLayout;
        auto formLy = new QFormLayout;
        formLy->addRow("Id", txtId);
        formLy->addRow("Titlu", txtTitlu);
        formLy->addRow("Artist", txtArtist);
        formLy->addRow("Gen", txtGen);
        stgLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdauga);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnCauta);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
    }
};