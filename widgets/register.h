#ifndef REGISTER_H
#define REGISTER_H
//===================登录界面=====================
//==============类名写错了========================
//==================应该是login===================
#include <QMainWindow>
#include "userinfo.h"

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT
signals:
    void signalLoginSuccess(UserInfo *info);

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private:
    Ui::Register *ui;

private slots:
    void on_pb_register_clicked();
    void on_pb_cancel_clicked();
    void on_pb_zhaomima_clicked();
};

#endif // REGISTER_H
