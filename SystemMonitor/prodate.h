#ifndef PRODATE_H
#define PRODATE_H
#include <QString>
#include <QList>

class ProDate
{
public:
    ProDate();
    explicit ProDate(QString s1, qint64 s2, qint64 s3, QString s4, qint64 m, qint64 p);
    ~ProDate();
    QString name;
    qint64 id;
    qint64 pid;
    QString stat;
    qint64 memory;
    qint64 priority;
};

#endif // PRODATE_H
