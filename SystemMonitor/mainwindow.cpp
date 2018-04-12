#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tablewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile file("/proc/stat");
    qint64 user,nice,sys,idle,iowait,irq,softirq;
    QString temp;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream >> temp >> user >> nice >> sys >> idle >> iowait >> irq >> softirq;
    all1 = user+nice+sys+idle+iowait+irq+softirq;
    idle1 = idle;
    file.close();

    ui->setupUi(this);
    for(int i=0;i<10;i++){
        buff1[i] = 0;
        buff2[i] = 0;
    }
    time_1s = new QTimer(this);
    //time_d = new QTimer(this);
    ui->label_6->setText(tr(get_hostname()));
    ui->label_7->setText(get_boot_time());
    ui->label_9->setText(get_os_type());
    ui->label_10->setText(get_processor().append("  ").append(get_Hz0()).append("MHz"));
    ui->label_11->setText(get_processor().append("  ").append(get_Hz1()).append("MHz"));
    ui->label_12->setText(get_processor().append("  ").append(get_Hz2()).append("MHz"));
    ui->label_13->setText(get_processor().append("  ").append(get_Hz3()).append("MHz"));
    flags = 0;
    connect(time_1s,&QTimer::timeout,this,&MainWindow::timeoutSlot);
    time_1s->start(1000);
    ui->tab_2 = new TableWidget(ui->tableView,ui->tab_2);
    nowTimeLabel = new QLabel(this);
    nowTimeLabel->setMinimumSize(200,30);
    nowTimeLabel->setFrameShape(QFrame::WinPanel);
    nowTimeLabel->setFrameShadow(QFrame::Sunken);
    ui->statusBar->addWidget(nowTimeLabel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeoutSlot()
{
    drawLine();
    QDateTime time = QDateTime::currentDateTime();
    QString nowTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    nowTimeLabel->setText(nowTime);
    nowTimeLabel->setAlignment(Qt::AlignCenter);

    ui->label_8->setText(QString::number(get_run_time_sec()).append("s"));
}

void MainWindow::drawLine()
{
    QVector<double> Xvalue(10);
    QVector<double> Y1value(10);
    QVector<double> Y2value(10);
    if(flags<10){
        buff1[flags] = calcu_cpu_rate();
        ui->cpulabel->setText(QString::number(buff1[flags],10,2).append("%"));
        buff2[flags] = get_mem_use_stat();
        ui->memlabel->setText(QString::number(buff2[flags],10,2).append("%"));
        for(int i = 0; i<=flags; i++){
            Xvalue[i] = i;
            Y1value[i] = buff1[i];
            Y2value[i] = buff2[i];
        }
        ui->qCustomPlot->addGraph();
        ui->qCustomPlot->graph(0)->setPen(QPen(Qt::red));
        ui->qCustomPlot->graph(0)->setData(Xvalue,Y1value);
        ui->qCustomPlot->xAxis->setRange(0,10);
        ui->qCustomPlot->yAxis->setRange(0,100);
        ui->qCustomPlot->xAxis->setLabel("time");
        ui->qCustomPlot->yAxis->setLabel("%");
        ui->qCustomPlot->xAxis->setTickLabels(false);
        ui->qCustomPlot->replot();


        ui->qCustomPlot2->addGraph();
        ui->qCustomPlot2->graph(0)->setPen(QPen(Qt::red));
        ui->qCustomPlot2->graph(0)->setData(Xvalue,Y2value);
        ui->qCustomPlot2->xAxis->setRange(0,10);

        ui->qCustomPlot2->yAxis->setRange(0,100);
        ui->qCustomPlot2->xAxis->setLabel("time");
        ui->qCustomPlot2->yAxis->setLabel("%");
        ui->qCustomPlot2->xAxis->setTickLabels(false);
        ui->qCustomPlot2->replot();
        flags++;
        return;
    }
    for(int i=0;i<9;i++){
        buff1[i] = buff1[i+1];
        buff2[i] = buff2[i+1];
    }
    buff1[9] = calcu_cpu_rate();
    ui->cpulabel->setText(QString::number(buff1[9],10,2).append("%"));
    buff2[9] = get_mem_use_stat();
    ui->memlabel->setText(QString::number(buff2[9],10,2).append("%"));

    for(int i=0;i<10;i++){
        Xvalue[i] = (flags - (9 - i));
        Y1value[i] = buff1[i];
        Y2value[i] = buff2[i];
    }

    ui->qCustomPlot->addGraph();
    ui->qCustomPlot->graph(0)->setPen(QPen(Qt::red));
    ui->qCustomPlot->graph(0)->setData(Xvalue,Y1value);
    ui->qCustomPlot->xAxis->setRange((flags-9),(10+flags-9));
    ui->qCustomPlot->yAxis->setRange(0,100);
    ui->qCustomPlot->xAxis->setLabel("time");
    ui->qCustomPlot->yAxis->setLabel("%");
    ui->qCustomPlot->xAxis->setTickLabels(false);
    ui->qCustomPlot->replot();

    ui->qCustomPlot2->addGraph();
    ui->qCustomPlot2->graph(0)->setPen(QPen(Qt::red));
    ui->qCustomPlot2->graph(0)->setData(Xvalue,Y2value);
    ui->qCustomPlot2->xAxis->setRange((flags-9),(10+flags-9));
    ui->qCustomPlot2->yAxis->setRange(0,100);
    ui->qCustomPlot2->xAxis->setLabel("time");
    ui->qCustomPlot2->yAxis->setLabel("%");
    ui->qCustomPlot2->xAxis->setTickLabels(false);
    ui->qCustomPlot2->replot();
    flags++;
    return;
}

double MainWindow::calcu_cpu_rate()
{
    QFile file("/proc/stat");
    qint64 user,nice,sys,idle,iowait,irq,softirq;
    qint64 all2,idle2;
    double usage;
    QString temp;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream >> temp >> user >> nice >> sys >> idle >> iowait >> irq >> softirq;
    all2 = user+nice+sys+idle+iowait+irq+softirq;
    idle2 = idle;
    file.close();
    usage = (double)(all2-all1-(idle2-idle1)) / (all2-all1)*100 ;
    usage = (usage*100+0.5)/100;
    return usage;
    /*
    FILE *fp;
    char buf[128];
    char cpu[5];

    long int user,nice,sys,idle,iowait,irq,softirq;

    long int all1,all2,idle1,idle2;
    double usage;

    fp = fopen("/proc/stat","r");
    if(fp == NULL)
    {
        perror("fopen:");
        exit (0);
    }


    fgets(buf,sizeof(buf),fp);

    sscanf(buf,"%s%ld%ld%ld%ld%ld%ld%ld",cpu,&user,&nice,&sys,&idle,&iowait,&irq,&softirq);

    all1 = user+nice+sys+idle+iowait+irq+softirq;
    idle1 = idle;
    rewind(fp);
    //第二次取数据
    sleep(1);
    memset(buf,0,sizeof(buf));
    cpu[0] = '\0';
    user=nice=sys=idle=iowait=irq=softirq=0;
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s%ld%ld%ld%ld%ld%ld%ld",cpu,&user,&nice,&sys,&idle,&iowait,&irq,&softirq);

    all2 = user+nice+sys+idle+iowait+irq+softirq;
    idle2 = idle;

    usage = (double)(all2-all1-(idle2-idle1)) / (all2-all1)*100 ;
    usage = (usage*100+0.5)/100;
    fclose(fp);
    return usage;
    */
}
