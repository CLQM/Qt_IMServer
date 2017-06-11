#include "listenclient.h"
#include "connectclient.h"
#include "logiclayer.h"

#include <QTcpSocket>
#include <QDebug>

QMap<QString,ConnectClient*> ListenClient::m_map;
/*非常重要的说明*/
List_UserInfo *ListenClient::m_userInfoList = new List_UserInfo;

ListenClient::ListenClient(QObject *parent) : QObject(parent)
{
    m_parent = parent;
    m_imServer = new QTcpServer(this);  //将Listenclient作为
    m_imServer->listen(QHostAddress::Any,55555);//用端口55555监听所有请求55555的ip
    connect(m_imServer,SIGNAL(newConnection()),
            this,SLOT(slotServerConnected()));
}

ListenClient::~ListenClient()
{}

void ListenClient::slotServerConnected(void)
{//新TCP的连接请求的槽
    ConnectClient *client = new ConnectClient(
                m_imServer->nextPendingConnection());//获得等待连接的tcpsocket(套接字)
//    QString id;
//    id = m_userInfoList->last().getUID();
//    m_map.insert(id,client);
    QString id;
    id = QString::number(m_userInfoList->size());
    m_map.insert(id,client);

    connect(client,SIGNAL(signalClientLoginSuccess()),
            this,SLOT(slotClientLoginSuccess()));
    connect(client,SIGNAL(signalSendAddFriendMsgtoClient(QString,QByteArray*)),
            this,SLOT(slotSendAddFriendMsgtoClient(QString,QByteArray*)));
    client->start();    //一个客户端一个线程
}
void ListenClient::slotClientLoginSuccess(void)
{//连接服务器成功
    emit signalClientLoginSuccess();
}


void ListenClient::slotSendAddFriendMsgtoClient(QString uid,QByteArray* buffer)
{//添加好有
    QMap<QString ,ConnectClient*>::const_iterator it;
    for(it = m_map.constBegin(); it != m_map.constEnd(); it++)
    {
        while(m_userInfoList->at(it.key().toInt()).getUID() == uid)
        {
            it.value()->slotSendMsgToClient(buffer);
            return;
        }
    }
}
