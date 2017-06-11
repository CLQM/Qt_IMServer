#include "statuinfo.h"
#include <QDebug>

StatuInfo::StatuInfo()
{
}

StatuInfo::StatuInfo(const QString &sid, const QString &sname,
                     const QString &sicon)
{
    updataStatuinfo(sid,sname,sicon);
}
StatuInfo::~StatuInfo()
{
}

void StatuInfo::updataStatuinfo(StatuInfo *info)
{
    m_SID = info->getSID();
    m_SName = info->getSName();
    m_SIcon = info->getSIcon();
}

void StatuInfo::updataStatuinfo(const QString &sid, const QString &sname,
                                const QString &sicon)
{
    m_SID = sid;
    m_SName = sname;
    m_SIcon = sicon;
}

void StatuInfo::clearStatuinfo(void)
{
    m_SID.clear();
    m_SName.clear();
    m_SIcon.clear();
}

void StatuInfo::printInfos(void)const
{
    qDebug() << "=======Statuinfo=========";
    qDebug() << "ID" << getSID();
    qDebug() << "Name" << getSName();
    qDebug() << "icon" << getSIcon();
    qDebug() << "=======regidsterinfo========";
}

QString *StatuInfo::packageinfos(void)
{
    QString *data = new QString();
    data->clear();

    data->append(getSID());
    data->append("|");
    data->append(getSName());
    data->append("|");
    data->append(getSIcon());

    return data;
}

void StatuInfo::setSID(const QString &sid)
{
    m_SID = sid;
}

const QString &StatuInfo::getSID(void)const
{
    return m_SID;
}

void StatuInfo::setSName(const QString &sname)
{
    m_SName = sname;
}

const QString &StatuInfo::getSName(void) const
{
    return m_SName;
}

void StatuInfo::setSIcon(const QString &sicon)
{
    m_SIcon = sicon;
}

const QString &StatuInfo::getSIcon(void)const
{
    return m_SIcon;
}
