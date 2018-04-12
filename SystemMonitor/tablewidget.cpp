#include "tablewidget.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPoint>

TableWidget::TableWidget(QTableView *tableView, QWidget *parent) :
    QWidget(parent)
{

    table = new TableModel(this);
    proxyModel = new QSortFilterProxyModel(this);
    tabView = tableView;
    proxyModel->setSourceModel(table);
    tableView->setModel(proxyModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    rightMenu = new QMenu(this);
    closePro = new QAction(this);
    refresh = new QAction("refresh",this);
    closePro->setText("close process");
    rightMenu->addAction(closePro);
    rightMenu->addAction(refresh);

    time = new QTimer(this);
    time->start(2000);
    connect(time,&QTimer::timeout,this,&TableWidget::reFresh);
    connect(refresh,&QAction::triggered,this,&TableWidget::reFresh);
    connect(closePro,&QAction::triggered,this,&TableWidget::closeP);
    connect(tableView,SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(clicked_rightMenu(const QPoint&)));


    get_pid_info(proInfo);

    table->setCurrencyList(proInfo);


}

void TableWidget::clicked_rightMenu(const QPoint &pos)
{

    rightMenu->exec(QCursor::pos());
}

void TableWidget::reFresh()
{
    get_pid_info(proInfo);

    table->setCurrencyList(proInfo);
}

void TableWidget::closeP()
{
    int rows = tabView->currentIndex().row();
    QModelIndex index = proxyModel->index(rows,1);
    QVariant data = proxyModel->data(index);
    qDebug()<<rows<<data.toString();
    QString cmd = QString("kill ").append(data.toString());

    system(cmd.toLatin1().data());
}

void TableWidget::timeoutSlot()
{

}