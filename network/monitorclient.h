#ifndef MONITORCLIENT_H
#define MONITORCLIENT_H

#include <QObject>
#include <QUdpSocket>

#include "improtocol.h"
#include "execusercmd.h"

class MonitorClient : public QObject
{
    Q_OBJECT
signals:
    void signalShowMessage(const QString &nick,
                     const QString &message);
public slots:
    void slotRecvMessage();
    void slotSendMessage(const UserInfo &recvUser,
                         const UserInfo &sendUser,
                         const QString &msg);

public:
    explicit MonitorClient(QObject *parent = 0);
    ~MonitorClient();

private:
    quint32 m_port;
    QUdpSocket *m_udpSocket;

    IMProtocol *m_protocol;
    ExecUserCmd *m_execUserCmd;
};

#endif // MONITORCLIENT_H
