#ifndef INFO_H
#define INFO_H
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include "prodate.h"


using namespace std;

double get_mem_use_stat();

QString get_processor();
QString get_Hz0();
QString get_Hz1();
QString get_Hz2();
QString get_Hz3();

void read_proc(ProDate &pidinfo, QString c_pid);
int get_pid_info(QList<ProDate> &processInfo);

QString get_boot_time();
char* get_hostname();
float get_run_time_sec();
QString get_os_type();



#endif // INFO_H
