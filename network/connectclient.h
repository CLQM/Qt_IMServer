#ifndef CONNECTSOCKET_H
#define CONNECTSOCKET_H

#include <QString>
#include <QList>
#include <QTcpSocket>
#include <QThread>
#include <QMap>

#include "improtocol.h"
#include "execusercmd.h"



class ConnectClient: public QThread
{
    Q_OBJECT

signals:
    void signalClientLoginSuccess();
    void signalSendAddFriendMsgtoClient(QString id,QByteArray* buffer);
public slots:
    void readyToRead();
    void slotSendMsgToClient(QByteArray *buffer);
    void slotSendAddFriendMsgtoClient(QString id,QByteArray* buffer);

public:
    ConnectClient(QTcpSocket *nect);
    ~ConnectClient();

    void recvMsg(void);
    void sendMsg(QString msg);
    void run();



private:
    QTcpSocket *m_socket;
    IMProtocol *m_protocol;

    ExecUserCmd *m_execUserCmd;
};



#endif // CONNECTSOCKET_H
