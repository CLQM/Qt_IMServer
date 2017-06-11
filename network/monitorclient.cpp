#include "monitorclient.h"


#include "logiclayer.h"

#include "mainwindow.h"

MonitorClient::MonitorClient(QObject *parent)
    : QObject(parent)
{
    m_port = 66666;
    m_udpSocket = new QUdpSocket();

    m_protocol = new IMProtocol();
    m_execUserCmd = new ExecUserCmd();

    connect(m_execUserCmd, SIGNAL(signalRecordChatInfo(UserInfo,UserInfo,QString)),
            (MainWindow *)parent, SLOT(slotRecordChatInfo(UserInfo,UserInfo,QString)));

#ifdef Q_OS_LINUX
     m_udpSocket->bind(m_port, QUdpSocket::ShareAddress);
#else //Q_OS_WIN32
     m_udpSocket->bind(m_port, QUdpSocket::ReuseAddressHint);
#endif
    connect(m_udpSocket, SIGNAL(readyRead()),
            this, SLOT(slotRecvMessage()));
}

MonitorClient::~MonitorClient()
{
    delete m_udpSocket;
    delete m_protocol;
    delete m_execUserCmd;
}

void MonitorClient::slotRecvMessage()
{
    while(m_udpSocket->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(buffer.data(), buffer.size());

        QDataStream in(buffer);
        m_protocol->unpackageMsg(in);
        m_execUserCmd->analysisProtocol(m_protocol);
    }
}

void MonitorClient::slotSendMessage(const UserInfo &recvUser,
                                    const UserInfo &sendUser,
                                    const QString &msg)
{
    QByteArray *buffer =
                    m_protocol->updataMsg(1, ERROR_INFO_NONE,
                          USER_OPE_CHAT, OPE_CMD_CHAT_PRIVATE,
                          recvUser.getUID().toInt(), sendUser.getUID().toInt(),
                          msg.size(), msg);

    m_udpSocket->writeDatagram(*buffer, QHostAddress::Broadcast, m_port);
}


