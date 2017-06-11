#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userinfo.h"
#include "listenclient.h"

#include <QDebug>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateOnlineInfoList();
    m_monitorClient = new MonitorClient(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotLoginSuccess(UserInfo *info)
{
    ui->le_name->setText(info->getRName());     //返回注册时的名字
    ui->le_sign->setText(info->getSelfSign());  //签名

    //获取全部的IP地址信息
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {//遍历地址信息
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {//主机地址协议是否为IPv4
            if(address.toString().contains("192.168"))
            {//如何包含"192..."的话返回真
                ui->le_ipAddr->setText(address.toString());
            }
        }
    }
    this->show();
}
void MainWindow::updateOnlineInfoList(void)
{//更新服务器在线人员数据
    ui->tw_userOnlineList->setRowCount(
        ListenClient::m_userInfoList->size());//有几个用户就用几行
    ui->tw_userOnlineList->setColumnCount(5);//userinfo的属性

    QStringList headers;
    headers << "UID" <<"NickName" << "NetYear" << "IpAddr" <<"port";
    //定义列名
    ui->tw_userOnlineList->setHorizontalHeaderLabels(headers);
    for(int row = 0; row < ListenClient::m_userInfoList->size(); row++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(
                       ListenClient::m_userInfoList->at(row).getUID()));
        ui->tw_userOnlineList->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(tr("%1").arg(
                       ListenClient::m_userInfoList->at(row).getRName()));
        ui->tw_userOnlineList->setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(tr("%1").arg(
                       ListenClient::m_userInfoList->at(row).getRTime()));
        ui->tw_userOnlineList->setItem(row, 2, newItem);
        newItem = new QTableWidgetItem(tr("%1").arg(
                       ListenClient::m_userInfoList->at(row).getIpAddr()));
        ui->tw_userOnlineList->setItem(row, 3, newItem);
        newItem = new QTableWidgetItem(tr("%1").arg(
                       ListenClient::m_userInfoList->at(row).getPort()));
        ui->tw_userOnlineList->setItem(row, 4, newItem);
    }
    /*使表格不可修改*/
    ui->tw_userOnlineList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::slotRecordChatInfo(const UserInfo &recvUser,
                                    const UserInfo &sendUser,
                                    const QString &msg)
{
    QString info = sendUser.getRName() + " to "
            + recvUser.getRName() + ": " +msg;

    ui->textBrowser->append(info);
}
