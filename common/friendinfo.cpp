#include "friendinfo.h"
#include <QDebug>

FriendInfo::FriendInfo()
{
    clearFriendInfo();
}

FriendInfo::FriendInfo(const QString &fid, const QString &remark)
{
    m_fid = fid;
    m_remark = remark;
}

FriendInfo::~FriendInfo()
{

}

void FriendInfo::updataFriendInfo(FriendInfo *info)
{
    m_fid = info->getFID();
    m_remark = info->getRemark();
}

void FriendInfo::updataFriendInfo(const QString &fid, const QString &remark)
{
    m_fid = fid;
    m_remark = remark;
}

void FriendInfo::clearFriendInfo(void)
{
    m_fid.clear();
    m_remark.clear();
}

void FriendInfo::printInfos(void) const
{
    qDebug() << "RegisterInfo-----------------------------------";
    qDebug() << "ID: " << getRID();
    qDebug() << "Name: " << getRName();
    qDebug() << "Password: " << getRPassword();
    qDebug() << "Time: " << getRTime();
    qDebug() << "IpAddrInfo-----------------------------------";
    qDebug() << "IpID: " << getIpID();
    qDebug() << "IpAddr: " << getIpAddr();
    qDebug() << "Port: " << getPort();
    qDebug() << "UserInfo-----------------------------------";
    qDebug() << "UID: " << getUID();
    qDebug() << "SelfSign: " << getSelfSign();
    qDebug() << "GroupInfo-----------------------------------";
    qDebug() << "GID: " << getGID();
    qDebug() << "GName: " << getGName();
    qDebug() << "FriendInfo-----------------------------------";
    qDebug() << "FID: " << getFID();
    qDebug() << "Remark: " << getRemark();
    qDebug() << "FriendInfo===================================";
}
QString *FriendInfo::packageinfos(void) const
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
    data->append("|");

    data->append(getGID());
    data->append("|");
    data->append(getGName());
    data->append("|");

    data->append(getFID());
    data->append("|");
    data->append(getRemark());

    return data;
}

const QString &FriendInfo::getFID(void) const
{
    return m_fid;
}
void FriendInfo::setFID(const QString &fid)
{
    m_fid = fid;
}

const QString &FriendInfo::getRemark(void) const
{
    return m_remark;
}
void FriendInfo::setRemark(const QString &remark)
{
    m_remark = remark;
}
