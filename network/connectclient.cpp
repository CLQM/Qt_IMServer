#include "connectclient.h"
#include "listenclient.h"

#include <QDebug>

ConnectClient::ConnectClient(QTcpSocket *nect)
{
    m_execUserCmd = new ExecUserCmd;
    m_protocol = new IMProtocol;
    m_socket = nect;

    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(readyToRead()));
    connect(m_execUserCmd, SIGNAL(signalSendMsgtoClient(QByteArray*)),
            this, SLOT(slotSendMsgToClient(QByteArray*)));
    connect(m_execUserCmd,SIGNAL(signalSendAddFriendMsgtoClient(QString,QByteArray*)),
            this,SLOT(slotSendAddFriendMsgtoClient(QString,QByteArray*)));

//    connect(m_execUserCmd, SIGNAL(signalSendMsgtoClient(QByteArray*)),
//            this, SLOT(slotSendMsgToClient(QByteArray*)));
//    connect(m_socket, SIGNAL(disconnected()),
//            m_socket, SLOT(deleteLater()));
}

ConnectClient::~ConnectClient()
{
    delete m_execUserCmd;
    delete m_protocol;
    delete m_socket;
}

void ConnectClient::run()
{
}

void ConnectClient::readyToRead()
{
    recvMsg();
}

void ConnectClient::recvMsg(void)
{
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_4_6);
    m_protocol->unpackageMsg(in);

    m_execUserCmd->analysisProtocol(m_protocol);
}

void ConnectClient::sendMsg(QString msg)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << msg;

    m_socket->write(buffer);
//    m_socket->disconnectFromHost();
}

void ConnectClient::slotSendAddFriendMsgtoClient(QString id,QByteArray* buffer)
{
    emit signalSendAddFriendMsgtoClient(id,buffer);
}

void ConnectClient::slotSendMsgToClient(QByteArray *buffer)
{
    m_socket->write(*buffer);
    emit signalClientLoginSuccess();
}

