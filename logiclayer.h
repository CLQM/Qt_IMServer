#ifndef LOGICLAYER_H
#define LOGICLAYER_H
//=============MVC中model===============

#include <QObject>
#include <QTimer>
#include "userinfo.h"
//#include "logfile.h"
#include "register.h"
#include "mainwindow.h"
#include "listenclient.h"

class Register;

class LogicLayer : public QObject
{
    Q_OBJECT
public:
    explicit LogicLayer(QObject *parent = 0);

signals:

public slots:
    void slotClientLoginSuccess();

private:
    Register *m_register;
    MainWindow *m_mainw;
    ListenClient *m_listen;
};

#endif // LOGICLAYER_H
