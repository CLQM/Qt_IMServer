#ifndef LOGFILE_H
#define LOGFILE_H
//==========日志文件=========
#include <QObject>

class LogFile : public QObject
{
    Q_OBJECT
public:
    explicit LogFile(QObject *parent = 0);

signals:

public slots:
};

#endif // LOGFILE_H
