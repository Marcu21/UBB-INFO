#pragma once
#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QSlider>
#include "service.h"
#include "TableModel.h"


class GUI : public QWidget {
    Service& service;
    MyTableModel* model;

public:
    GUI(Service& service) : service(service) {
        model = new MyTableModel(this);
        initGUI();
        loadData();
        initConnect();
    }

private:
    QTableView* tableView = new QTableView;
    QPushButton* btnExit = new QPushButton("&Exit");
    QPushButton* btnAdauga = new QPushButton("&Adauga");
    QPushButton* btnSterge = new QPushButton("&Sterge");
    QPushButton* btnModifica = new QPushButton("&Modifica");
    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtDenumire = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtCilindrii = new QLineEdit;

    void initConnect() {
        //Conecteaza butoanele la functionalitati
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            close();
        });
        QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
            auto id = txtId->text().toInt();
            auto denumire = txtDenumire->text().toStdString();
            auto tip = txtTip->text().toStdString();
            auto cilindrii = txtCilindrii->text().toInt();
            try {
                service.adauga(id, denumire, tip, cilindrii);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
            auto id = txtId->text().toInt();
            try {
                service.sterge(id);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
            auto id = txtId->text().toInt();
            auto denumire = txtDenumire->text().toStdString();
            auto tip = txtTip->text().toStdString();
            auto cilindrii = txtCilindrii->text().toInt();
            try {
                service.modifica(id, denumire, tip, cilindrii);
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
            loadData();
        });
        QObject::connect(tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, [&](const QModelIndex &current, const QModelIndex &previous) {
            if (current.isValid()) {
                txtId->setText(model->data(model->index(current.row(), 0), Qt::DisplayRole).toString());
                txtDenumire->setText(model->data(model->index(current.row(), 1), Qt::DisplayRole).toString());
                txtTip->setText(model->data(model->index(current.row(), 2), Qt::DisplayRole).toString());
                txtCilindrii->setText(model->data(model->index(current.row(), 3), Qt::DisplayRole).toString());
            }
        });
    }

    void loadData() {
        //Incarca datele in tabel
        auto elems = service.get_all_sortat();
        model->update(elems);
    }

    void initGUI() {
        //Initializeaza partea de gui
        QHBoxLayout* lyMain = new QHBoxLayout;
        setLayout(lyMain);

        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        lyMain->addWidget(tableView);

        QVBoxLayout* stgLy = new QVBoxLayout;
        QFormLayout* formLy = new QFormLayout;
        formLy->addRow("Id", txtId);
        formLy->addRow("Denumire", txtDenumire);
        formLy->addRow("Tip", txtTip);
        formLy->addRow("Cilindrii", txtCilindrii);
        stgLy->addLayout(formLy);

        QHBoxLayout* lyBtn = new QHBoxLayout;
        lyBtn->addWidget(btnAdauga);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        lyBtn->addWidget(btnExit);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
    }
};
