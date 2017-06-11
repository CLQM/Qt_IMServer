#include "ipaddrinfo.h"
#include <QDebug>
IpAddrInfo::IpAddrInfo()
{
    clearIpAddrInfo();
}

IpAddrInfo::IpAddrInfo(const QString &ipid, const QString &ipaddr,
                       const QString &port)
{//创建
    updataIpAddrInfo(ipid,ipaddr,port);
}

IpAddrInfo::~IpAddrInfo()
{
}

void IpAddrInfo::updataIpAddrInfo(IpAddrInfo *info)
{//更新
    m_IpID = info->getIpID();
    m_IpAddr = info->getIpAddr();
    m_Port = info->getPort();
}

void IpAddrInfo::updataIpAddrInfo(const QString &ipid,
                      const QString &ipaddr,const QString &port)
{
    m_IpID = ipid;
    m_IpAddr = ipaddr;
    m_Port = port;
}

void IpAddrInfo::clearIpAddrInfo(void)
{
    m_IpID.clear();
    m_IpAddr.clear();
    m_Port.clear();
}

void IpAddrInfo::printInfos(void) const
{
    qDebug() << "=========IpAddrInfo======";
    qDebug() << "ID" << getIpID();
    qDebug() << "Name" << getIpAddr();
    qDebug() << "Sex" << getPort();
    qDebug() << "=========IpAddrInfo======";
}
QString *IpAddrInfo::packageinfos(void)
{
    QString *data = new QString();
    data->clear();

    data->append(getIpID());
    data->append("|");
    data->append(getIpAddr());
    data->append("|");
    data->append(getPort());

    return data;
}

const QString &IpAddrInfo::getIpID(void) const
{
    return m_IpID;
}
void IpAddrInfo::setIpID(const QString &ipid)
{
    m_IpID = ipid;
}

const QString &IpAddrInfo::getIpAddr(void) const
{
    return m_IpAddr;
}
void IpAddrInfo::setIpAddr(const QString &ipaddr)
{
    m_IpAddr = ipaddr;
}

const QString &IpAddrInfo::getPort(void) const
{
    return m_Port;
}
void IpAddrInfo::setPort(const QString &port)
{
    m_Port = port;
}
