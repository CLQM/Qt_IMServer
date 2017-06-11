#ifndef LISTENCLIENT_H
#define LISTENCLIENT_H
//==========TCP监听client并调用connrect连接======
#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QList>
#include <QMap>
#include <QString>

#include "common.h"
#include "connectclient.h"

class ListenClient : public QObject
{
    Q_OBJECT
signals:
    void signalClientLoginSuccess();    //为何在connect中也有同名

public slots:
    void slotServerConnected(void);
    void slotClientLoginSuccess(void);
    void slotSendAddFriendMsgtoClient(QString uid, QByteArray* buffer);

public:
    explicit ListenClient(QObject *parent = 0);
    ~ListenClient();
    static List_UserInfo *m_userInfoList;
    static QMap<QString,ConnectClient*> m_map;

private:
    QTcpServer *m_imServer;
    QObject *m_parent;
};



#endif // LISTENCLIENT_H
