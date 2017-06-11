#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//=============服务器主界面=========
#include <QMainWindow>

#include "monitorclient.h"


class UserInfo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateOnlineInfoList(void);

public slots:
    void slotLoginSuccess(UserInfo *info);
    void slotRecordChatInfo(const UserInfo &recvUser,
                                const UserInfo &sendUser,
                                const QString &msg);

private:
    Ui::MainWindow *ui;
    MonitorClient *m_monitorClient;
};

#endif // MAINWINDOW_H
