#include "userinfo.h"
#include <QDebug>

UserInfo::UserInfo()
{
    clearUserInfo();
}

UserInfo::UserInfo(const QString &uid,
                   const QString &selfsign)
{
    updataUserInfo(uid,selfsign);
}

UserInfo::~UserInfo()
{}

void UserInfo::updataUserInfo(UserInfo *info)
{
    updataIpAddrInfo(info->getIpID(),info->getIpAddr(),info->getPort());
    updataRegisterInfo(info->getRID(),info->getRName(), info->getRPassword(),
                       info->getRTime());
    m_UID = info->getUID();
    m_SelfSign = info->getSelfSign();
}

void UserInfo::updataUserInfo(const QString &uid,
                              const QString &selfsign)
{
    m_UID = uid;
    m_SelfSign =selfsign;
}
void UserInfo::clearUserInfo()
{
    m_UID.clear();
    m_SelfSign.clear();
}

void UserInfo::printInfos(void) const
{
    qDebug() << "=======UserInfo=========";
    qDebug() << "ID" << getUID();
    qDebug() << "Self Sign" << getSelfSign();
    qDebug() << "=======UserInfo========";
}

QString *UserInfo::packageinfos(void)
{
    QString *data = new QString();
    data->clear();

    data->append(getRID());
    data->append("|");
    data->append(getRName());
    data->append("|");
    data->append(getRPassword());
    data->append("|");
    data->append(getRTime());
    data->append("|");

    data->append(getIpID());
    data->append("|");
    data->append(getIpAddr());
    data->append("|");
    data->append(getPort());
    data->append("|");

    data->append(getUID());
    data->append("|");
    data->append(getSelfSign());

    return data;
}

void UserInfo::setUID(const QString &uid)
{
    m_UID = uid;
}

const QString &UserInfo::getUID(void) const
{
    return m_UID;
}

void UserInfo::setSelfSign(const QString &selfsign)
{
    m_SelfSign = selfsign;
}

const QString &UserInfo::getSelfSign(void) const
{
    return m_SelfSign;
}
