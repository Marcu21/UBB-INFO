#include "../service/locatar_service.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include "../utils/observer.h"
#include <QTableView>
#include <QStandardItemModel>

class NotificariGUI : public QWidget, public Observer {
    locatar_service &service;
    QStandardItemModel *model = new QStandardItemModel(this);
    QTableView *tableView = new QTableView(this);

public:
    NotificariGUI(locatar_service &service) : service{service} {
        initGUI();
        loadData();
        initConnect();
    };

private:
    QLineEdit *txtApartament = new QLineEdit;
    QLineEdit *txtNumar = new QLineEdit;
    QLineEdit *txtFisier = new QLineEdit;
    QPushButton *btnAdauga = new QPushButton{"&Adauga notificare"};
    QPushButton *btnSterge = new QPushButton{"&Sterge toate notificarile"};
    QPushButton *btnGenereaza = new QPushButton{"&Genereaza apartamente"};
    QPushButton *btnExportHTML = new QPushButton{"&Export HTML"};
    QPushButton *btnExportCSV = new QPushButton{"&Export CSV"};
    QPushButton *btnReload = new QPushButton{"&Reload"};
    QPushButton *btnNewWindow = new QPushButton{"&NewWindow"};
    QPushButton *btnExit = new QPushButton{"&Exit"};

    void initGUI() {
        QHBoxLayout *lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        tableView->setModel(model);
        tableView->horizontalHeader()->setStretchLastSection(true);
        lyMain->addWidget(tableView);

        auto stgLy = new QVBoxLayout;
        auto formLy = new QFormLayout;
        formLy->addRow("Apartament", txtApartament);
        formLy->addRow("Numar", txtNumar);
        formLy->addRow("Fisier", txtFisier);
        stgLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdauga);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnGenereaza);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnExportHTML);
        lyBtn->addWidget(btnExportCSV);
        lyBtn->addWidget(btnReload);
        lyBtn->addWidget(btnNewWindow);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
    }

    void initConnect() {
        service.addObserver(this);
        QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
            int apartament = txtApartament->text().toInt();
            service.add_notification(apartament);
            loadData();
        });
        QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
            service.clear_notifications();
            loadData();
        });
        QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
            int numar = txtNumar->text().toInt();
            service.generate_notifications(numar);
            loadData();
        });

        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            close();
        });

        QObject::connect(btnExportHTML, &QPushButton::clicked, [&]() {
            QString fisier = txtFisier->text();
            try {
                service.export_to_html(fisier.toStdString());
            }
            catch (std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });

        QObject::connect(btnExportCSV, &QPushButton::clicked, [&]() {
            QString fisier = txtFisier->text();
            try {
                service.export_to_csv(fisier.toStdString());
            }
            catch (std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });

        QObject::connect(btnReload, &QPushButton::clicked, [&]() {
            loadData();
        });

        QObject::connect(btnNewWindow, &QPushButton::clicked, [&]() {
            auto nW = new NotificariGUI { service };
            nW->show();
        });
    }

    void update() override {
        loadData();
    }

    void loadData() {
        model->clear();
        model->setHorizontalHeaderLabels({"Apartment"});
        for (int apt : service.get_notifications()) {
            QStandardItem *item = new QStandardItem(QString::number(apt));
            model->appendRow(item);
        }
    }
};
