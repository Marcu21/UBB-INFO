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

class MyTableModel : public QAbstractTableModel {

private:
    vector<Melodie> elemente;

public:
    MyTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return elemente.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid())
            return QVariant();

        const Melodie &elem = elemente[index.row()];
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0:
                    return QString::number(elem.get_id());
                case 1:
                    return QString::fromStdString(elem.get_titlu());
                case 2:
                    return QString::fromStdString(elem.get_artist());
                case 3:
                    return QString::number(elem.get_rank());
            }
        } else if (role == Qt::ForegroundRole && elem.get_id() > 0) {
            return QBrush(Qt::darkGreen);
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return QStringLiteral("ID");
                case 1: return QStringLiteral("Nume");
                case 2: return QStringLiteral("Tip");
                case 3: return QStringLiteral("Pret");
                default: return QString();
            }
        }
        return QVariant();
    }

    void update(const vector<Melodie>& newElements) {
        beginResetModel();
        elemente = newElements;
        endResetModel();
    }
};

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
    QPushButton* btnCauta = new QPushButton("&Cauta");
    QPushButton* btnSortare = new QPushButton("&Sortare");
    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;
    QSlider* slider = new QSlider(Qt::Horizontal);

    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            QMessageBox::information(nullptr, "Info", "Exit button clicked");
            close();
        });
        QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
            auto id = txtId->text().toInt();
            auto nume = txtNume->text().toStdString();
            auto tip = txtTip->text().toStdString();
            auto pret = txtPret->text().toDouble();
            try {
                service.adauga(id, nume, tip, pret);
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
        QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
            auto id = txtId->text().toInt();
            try {
                auto elem = service.cauta(id);
                QMessageBox::information(nullptr, "Info", QString::fromStdString(elem.get_titlu()) + " " + QString::fromStdString(elem.get_artist()) + " " + QString::number(elem.get_rank()));
            }
            catch (const std::runtime_error& ex) {
                QMessageBox::warning(nullptr, "Warning", ex.what());
            }
        });
        /*QObject::connect(btnSortare, &QPushButton::clicked, [&]() {
            auto elems = service.sortare();
            model->updateElements(elems);
            tableView->viewport()->update();
        });*/
        QObject::connect(tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, [&](const QModelIndex &current, const QModelIndex &previous) {
            if (current.isValid()) {
                txtId->setText(model->data(model->index(current.row(), 0), Qt::DisplayRole).toString());
                txtNume->setText(model->data(model->index(current.row(), 1), Qt::DisplayRole).toString());
                txtTip->setText(model->data(model->index(current.row(), 2), Qt::DisplayRole).toString());
                txtPret->setText(model->data(model->index(current.row(), 3), Qt::DisplayRole).toString());
                slider->setValue(model->data(model->index(current.row(), 3), Qt::DisplayRole).toInt());
            }
        });
    }

    void loadData() {
        auto elems = service.get_all();
        model->update(elems);
    }

    void initGUI() {
        QHBoxLayout* lyMain = new QHBoxLayout;
        setLayout(lyMain);

        tableView->setModel(model);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        lyMain->addWidget(tableView);

        QVBoxLayout* stgLy = new QVBoxLayout;
        QFormLayout* formLy = new QFormLayout;
        formLy->addRow("Id", txtId);
        formLy->addRow("Nume", txtNume);
        formLy->addRow("Tip", txtTip);
        formLy->addRow("Pret", txtPret);
        stgLy->addLayout(formLy);

        QHBoxLayout* lyBtn = new QHBoxLayout;
        lyBtn->addWidget(btnAdauga);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        lyBtn->addWidget(btnExit);
        lyBtn->addWidget(btnCauta);
        lyBtn->addWidget(btnSortare);
        stgLy->addLayout(lyBtn);

        lyMain->addLayout(stgLy);
        slider->setRange(1, 10);
        formLy->addRow("Slider", slider);
    }
};
