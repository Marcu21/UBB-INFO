#pragma once
#pragma once
#pragma once
#include <QAbstractTableModel>
#include "../domain/locatar.h"
#include <vector>
#include <qdebug.h>
#include <QFont>
#include <QBrush>


using namespace std;

class TableModel : public QAbstractTableModel {
    std::vector<Locatar> locatari;
public:
    TableModel(const std::vector<Locatar>& locatari) : locatari{ locatari } {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return locatari.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        //qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
        if (role == Qt::FontRole) {
            QFont f;
            f.setItalic(index.row());
            f.setBold(index.row());
            return f;
        }
        if (role == Qt::ForegroundRole)
        {
            Locatar t = locatari[index.row()];
            if (t.get_apartament() > 0)
                return QBrush(Qt::darkGreen);
        }
        if (role == Qt::DisplayRole) {
            Locatar p = locatari[index.row()];
            if (index.column() == 0) {
                return QString::number(p.get_apartament());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(p.get_nume_proprietar());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(p.get_tip_apartament());
            }
            else if (index.column() == 3) {
                return QString::number(p.get_suprafata());
            }
        }

        return QVariant{};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return QStringLiteral("Apartament");
                case 1: return QStringLiteral("Proprietar");
                case 2: return QStringLiteral("Suprafata");
                case 3: return QStringLiteral("Tip");
                default: return QString();
            }
        }
        return QVariant();
    }

    void setLocatari(const std::vector<Locatar>& newLocatari) {
        beginResetModel();
        locatari = newLocatari;
        endResetModel();
    }

    void addLocatar(const Locatar& locatar) {
        int newRow = locatari.size();
        beginInsertRows(QModelIndex(), newRow, newRow);
        locatari.push_back(locatar);
        endInsertRows();
    }

    void removeLocatar(int index) {
        if (index >= 0 && index < locatari.size()) {
            beginRemoveRows(QModelIndex(), index, index);
            locatari.erase(locatari.begin() + index);
            endRemoveRows();
        }
    }
    Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
};