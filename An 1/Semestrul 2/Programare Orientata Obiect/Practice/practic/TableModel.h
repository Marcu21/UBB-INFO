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

class MyTableModel : public QAbstractTableModel {
    //Modelul de tabel

private:
    vector<Utilaj> elemente;
public:
    MyTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        //Returneaza nr de linii
        return elemente.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        //Returneaza nr de coloane
        return 5;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        //Initializeaza coloanele tabelului
        if (!index.isValid())
            return QVariant();

        const Utilaj &elem = elemente[index.row()];
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0:
                    return QString::number(elem.get_id());
                case 1:
                    return QString::fromStdString(elem.get_denumire());
                case 2:
                    return QString::fromStdString(elem.get_tip());
                case 3:
                    return QString::number(elem.get_cilindrii());
                case 4:
                {
                    int count = 0;
                    for (const Utilaj &el : elemente) {
                        if (el.get_tip() == elem.get_tip()) {
                            ++count;
                        }
                    }
                    return QString::number(count);
                }
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        //Initializeaza headerul tabelului
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return QStringLiteral("ID");
                case 1: return QStringLiteral("Denumire");
                case 2: return QStringLiteral("Tip");
                case 3: return QStringLiteral("Cilindrii");
                case 4: return QStringLiteral("Nr");
                default: return QString();
            }
        }
        return QVariant();
    }

    void update(const vector<Utilaj>& newElements) {
        //Refreshuieste tabelul
        beginResetModel();
        elemente = newElements;
        endResetModel();
    }
};