#include "prodate.h"

ProDate::ProDate()
{
}

ProDate::ProDate(QString s1, qint64 s2, qint64 s3, QString s4, qint64 m, qint64 p)
{
    name = s1;
    id = s2;
    pid = s3;
    stat = s4;
    memory = m;
    priority = p;
}
ProDate::~ProDate()
{

}
