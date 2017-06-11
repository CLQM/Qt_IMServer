#include "logiclayer.h"
#include <QDebug>

LogicLayer::LogicLayer(QObject *parent) : QObject(parent)
{
    m_listen = new ListenClient();
    m_register = new Register();
    m_mainw = new MainWindow(); //没写不报错???????


    m_register->show();

    connect(m_register,SIGNAL(signalLoginSuccess(UserInfo*)),
            m_mainw,SLOT(slotLoginSuccess(UserInfo*)));
    connect(m_listen,SIGNAL(signalClientLoginSuccess()),
            this,SLOT(slotClientLoginSuccess()));//客户端连接成功
}

void LogicLayer::slotClientLoginSuccess()
{//客户端连接成功，更新一下服务器中的在线人员信息
    m_mainw->updateOnlineInfoList();

}
