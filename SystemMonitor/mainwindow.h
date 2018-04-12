#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "tablewidget.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    double calcu_cpu_rate();
    double buff1[10];
    double buff2[10];
    ~MainWindow();
public slots:
    void timeoutSlot();
    void drawLine();
private:
    Ui::MainWindow *ui;
    QTimer *time_1s;
    //QTimer *time_d;
    qint64 flags;
    QLabel *nowTimeLabel;
    qint64 all1,idle1;
};

#endif // MAINWINDOW_H
