#include "info.h"
#include <QDebug>
#include <time.h>




//return free mem mb
double get_mem_use_stat()
{
    string str;
    double use;
    unsigned long memtotal,memfree,memavailable,membuffers,memcached;
    std::ifstream meminfo("/proc/meminfo");
    meminfo>>str>>memtotal>>str;
    meminfo>>str>>memfree>>str;
    meminfo>>str>>memavailable>>str;
    meminfo>>str>>membuffers>>str;
    meminfo>>str>>memcached>>str;
    use = (double)(100.0*(memtotal-memfree+membuffers+memcached)/memtotal);
    return use;
}




//get cpu information
QString get_processor()
{
    int i=0;
    QString processor;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str=stream.readLine();
        if(i==3){
            processor=str;
            break;
        }
        i++;
    }
    processor=processor.mid(13,56);
    file.close();
    return processor;
}
QString get_Hz0()
{
    int i=0;
    QString Hz0;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str=stream.readLine();
        if(i==6){
            Hz0=str;
            break;
        }
        i++;
    }
    Hz0=Hz0.mid(11,18);
    file.close();
    return Hz0;
}
QString get_Hz1()
{
    int i=0;
    QString Hz1;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str=stream.readLine();
        if(i==36){
            Hz1=str;
            break;
        }
        i++;
    }
    Hz1=Hz1.mid(11,18);
    file.close();
    return Hz1;
}
QString get_Hz2()
{
    int i=0;
    QString Hz2;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str=stream.readLine();
        if(i==66){
            Hz2=str;
            break;
        }
        i++;
    }
    Hz2=Hz2.mid(11,18);
    file.close();
    return Hz2;
}
QString get_Hz3()
{
    int i=0;
    QString Hz3;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str=stream.readLine();
        if(i==96){
            Hz3=str;
            break;
        }
        i++;
    }
    Hz3=Hz3.mid(11,18);
    file.close();
    return Hz3;
}



void read_proc(ProDate &pidinfo,QString c_pid)
{

    QString temp;
    QString filename = QString("/proc/%1/stat").arg(c_pid);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream>>pidinfo.id>>pidinfo.name>>pidinfo.stat>>pidinfo.pid>>temp>>temp;
    stream>>temp>>temp>>temp>>temp>>temp>>temp;
    stream>>temp>>temp>>temp>>temp>>temp>>temp;
    stream>>pidinfo.priority>>temp>>temp>>temp>>temp>>pidinfo.memory;
    pidinfo.name.remove("(");
    pidinfo.name.remove(")");
    file.close();
}
int get_pid_info(QList<ProDate> &processInfo)
{
    DIR *dir;
    struct dirent *ptr;
    int i=0;
    processInfo.clear();
    if(!(dir=opendir("/proc")))
        return 0;
    while((ptr=readdir(dir))!=false)
    {
        if(ptr->d_name[0]>='1' && ptr->d_name[0]<='9')
        {
            ProDate info;
            read_proc(info,ptr->d_name);
            processInfo.append(info);
            i++;
        }
    }
    closedir(dir);
    return i;
}






char* get_hostname()
{
    FILE* fp;
    char host[8];
    char *hostname;
    hostname=(char*)malloc(7*sizeof(char));
    fp=fopen("/proc/sys/kernel/hostname","r");
    fgets(host,sizeof(host),fp);
    sscanf(host,"%s",hostname);
    fclose(fp);
    return hostname;
}
float get_run_time_sec()
{
    FILE* fp;
    float runTime;
    char time[32];
    fp=fopen("/proc/uptime","r");
    fgets(time,sizeof(time),fp);
    sscanf(time,"%f",&runTime);
    fclose(fp);
    return runTime;
}

QString get_boot_time()
{
    QString boot;
    time_t cur_time = 0;
    time_t boot_time = 0;
    struct tm *ptm = NULL;
    time_t runtime;
    QString week[7]={"星期天","星期一","星期二","星期三","星期四","星期五","星期六"};
    runtime=(time_t)(get_run_time_sec());
    time(&cur_time);
    boot_time = cur_time - runtime;
    ptm = localtime(&boot_time);
    boot=QString("%1-%2-%3 %4:%5:%6 %7").arg(ptm->tm_year+1900).arg(ptm->tm_mon+1).arg(ptm->tm_mday).arg(ptm->tm_hour).arg(ptm->tm_min).arg(ptm->tm_sec).arg(week[ptm->tm_wday]);
    return boot;
}

QString get_os_type()
{
    QString os;
    char ostype[6],osrelease[8];
    char buff1[16],buff2[16];
    FILE *fp1,*fp2;
    fp1=fopen("/proc/sys/kernel/ostype","r");
    fp2=fopen("/proc/sys/kernel/osrelease","r");
    fgets(buff1,sizeof(buff1),fp1);
    fgets(buff2,sizeof(buff2),fp2);
    sscanf(buff1,"%s",ostype);
    sscanf(buff2,"%s",osrelease);
    os=QString("%1 %2").arg(ostype).arg(osrelease);
    fclose(fp1);
    fclose(fp2);
    return os;
}
