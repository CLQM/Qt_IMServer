#include "registerinfo.h"
#include <QDebug>

RegisterInfo::RegisterInfo()
{//申请内存空间
    clearRegisterInfo();
}

RegisterInfo::RegisterInfo(const QString &rid, const QString &name,
                           const QString &password, const QString &time)
{
    updataRegisterInfo(rid,name,password,time);
}

RegisterInfo::~RegisterInfo()
{
    //this->clearRegisterinfo();  多余的操作，因为系统会释放
}

void RegisterInfo::updataRegisterInfo(RegisterInfo *info)
{//赋值函数
    m_RID = info->getRID();
    m_RName = info->getRName();
    m_RPassword = info->getRPassword();
    m_RTime = info->getRTime();
}

void RegisterInfo::updataRegisterInfo(const QString &rid, const QString &name,
                                      const QString &password, const QString &time)
{
    m_RID = rid;
    m_RName = name;
    m_RPassword = password;
    m_RTime  = time;
}

void RegisterInfo::clearRegisterInfo(void)
{//清除对象的
    m_RID.clear();
    m_RName.clear();
    m_RPassword.clear();
    m_RTime.clear();
}

void RegisterInfo::printInfos(void) const
{
    qDebug() << "=======registerinfo=========";
    qDebug() << "ID" << getRID();
    qDebug() << "Name" << getRName();
    qDebug() << "Password" << getRPassword();
    qDebug() << "Time" << getRTime();
    qDebug() << "=======regidsterinfo========";
}

QString *RegisterInfo::packageinfos(void)
{
    QString *data = new QString();
    data->clear();      //防止乱数据

    data->append(getRID());
    data->append("|");
    data->append(getRName());
    data->append("|");
    data->append(getRPassword());
    data->append("|");
    data->append(getRTime());

    return data;
}

void RegisterInfo::setRID(const QString &pid)
{
    m_RID = pid;
}

const QString &RegisterInfo::getRID(void) const
{
    return m_RID;
}

void RegisterInfo::setRName(const QString &name)
{
    m_RName = name;
}

const QString &RegisterInfo::getRName() const
{
    return m_RName;
}

void RegisterInfo::setRPassword(const QString &password)
{
    m_RPassword = password;
}

const QString &RegisterInfo::getRPassword() const
{
    return m_RPassword;
}

void RegisterInfo::setRTime(const QString &time)
{
    m_RTime = time;
}

const QString &RegisterInfo::getRTime() const
{
    return m_RTime;
}


