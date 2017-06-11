#include "register.h"
#include "ui_register.h"

#include "userinfo.h"
#include "sqlanalysis.h"

#include <QMessageBox>
#include <QDebug>

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pb_register_clicked()
{//登录按钮
    UserInfo *info =SQLAnalysis::selectUserInfo(ui->le_accounts->text());
    if(info->getRPassword() == ui->le_password->text())
    {//密码正确
        emit signalLoginSuccess(info);
        this->hide();//隐藏登录界面
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("ERROR:You's uid or password!");//消息内容
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Retry|
                                  QMessageBox::Cancel); //Retry/cancal
        msgBox.setDefaultButton(QMessageBox::Retry);    //Retry

        int ret = msgBox.exec();    //==show()
                                    //返回值由用户的点击决定
        switch(ret){
        case  QMessageBox::Retry:
            ui->le_accounts->setFocus();    //把键盘输入焦点给这个窗口部件
            msgBox.close();
            break;
        case  QMessageBox::Cancel:
            ui->le_accounts->setFocus();
            break;
        default:
            break;
        }
    }
}

void Register::on_pb_cancel_clicked()
{
    this->close();
}

void Register::on_pb_zhaomima_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("你都忘了谁还能知道？");//消息内容
    msgBox.setInformativeText("再想一想可能就想起来了?");
    msgBox.setStandardButtons(QMessageBox::Retry|
                              QMessageBox::Cancel); //Retry/cancal
    msgBox.setDefaultButton(QMessageBox::Retry);    //Retry

    int ret = msgBox.exec();    //==show()
                                //返回值由用户的点击决定
    switch(ret){
    case  QMessageBox::Retry:
        msgBox.close();
        break;
    case  QMessageBox::Cancel:

        break;
    default:
        break;
    }
}
