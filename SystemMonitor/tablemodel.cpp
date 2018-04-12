#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfDate.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}
//! [1]

//! [2]
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfDate.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        ProDate pair = listOfDate.at(index.row());
        if (index.column() == 0)
            return pair.name;
        else if (index.column() == 1)
            return pair.id;
        else if (index.column() == 2)
            return pair.pid;
        else if (index.column() == 3)
            return pair.stat;
        else if (index.column() == 4)
            return pair.memory;
        else if (index.column() == 5)
            return pair.priority;
    }
    return QVariant();
}
//! [2]

//! [3]
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");

            case 1:
                return tr("ID");
            case 2:
                return tr("PPID");
            case 3:
                return tr("Stat");
            case 4:
                return tr("Memory(kb)");
            case 5:
                return tr("Priority");
            default:
                return QVariant();
        }
    }
    return QVariant();
}
//! [3]

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        ProDate p = listOfDate.value(row);

        if (index.column() == 0)
            p.name = value.toString();
        else if (index.column() == 1)
            p.id = value.toInt();
        else if (index.column() == 2)
            p.pid = value.toInt();
        else if (index.column() == 3)
            p.stat = value.toString();
        else if (index.column() == 4)
            p.memory = value.toInt();
        else if (index.column() == 5)
            p.priority = value.toInt();
        else
            return false;

        listOfDate.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}



//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]

QList<ProDate> TableModel::getList()
{
    return listOfDate;
}

void TableModel::setCurrencyList(const QList<ProDate> &list)
{
    beginResetModel();
    listOfDate = list;
    endResetModel();
}
