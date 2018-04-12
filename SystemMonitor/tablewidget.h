#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTimer>
#include <QWidget>
#include "tablemodel.h"
#include "info.h"
#include <QTableView>
#include <QAction>
#include <QMenu>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE


class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QTableView *tableView,QWidget *parent = 0);

signals:

public slots:
    void timeoutSlot();
    void clicked_rightMenu(const QPoint &pos);
    void closeP();
    void reFresh();

private:
    QTableView *tabView;
    QTimer *time;
    TableModel *table;
    QSortFilterProxyModel *proxyModel;
    QList<ProDate> proInfo;
    QMenu *rightMenu;
    QAction *closePro;
    QAction *refresh;
    //int rows;
};

#endif // TABLEWIDGET_H
