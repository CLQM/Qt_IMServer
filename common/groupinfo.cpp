#include "groupinfo.h"

#include <QDebug>

GroupInfo::GroupInfo()
{
    clearGroupInfo();
}

GroupInfo::GroupInfo(const QString &gid, const QString &gname)
{
    m_gid = gid;
    m_gname = gname;
}

GroupInfo::~GroupInfo()
{}

void GroupInfo::updataGroupInfo(GroupInfo *info)
{
    m_gid = info->getGID();
    m_gname = info->getGName();
}

void GroupInfo::updataGroupInfo(
        const QString &gid, const QString &gname)
{
    m_gid = gid;
    m_gname = gname;
}

void GroupInfo::clearGroupInfo()
{
    m_gid.clear();
    m_gname.clear();
}

void GroupInfo::printInfos() const
{
    qDebug() << "UserInfo-----------------------------------";
    qDebug() << "UID: " << getUID();
    qDebug() << "SelfSign: " << getSelfSign();
    qDebug() << "GroupInfo-----------------------------------";
    qDebug() << "GID: " << getGID();
    qDebug() << "GName: " << getGName();
    qDebug() << "GroupInfo===================================";
}

QString *GroupInfo::packageinfos()
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

    return data;
}

const QString &GroupInfo::getGID() const
{
    return m_gid;
}
void GroupInfo::setGID(const QString &gid)
{
    m_gid = gid;
}

const QString &GroupInfo::getGName(void) const
{
    return m_gname;
}
void GroupInfo::setGName(const QString &gname)
{
    m_gname = gname;
}
