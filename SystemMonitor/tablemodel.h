#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "prodate.h"



class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void setCurrencyList(const QList<ProDate> &list);
    //bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    //bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<ProDate> getList();
signals:

private:
    QList<ProDate> listOfDate;

};

#endif // TABLEMODEL_H
