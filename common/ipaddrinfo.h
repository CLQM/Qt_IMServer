#ifndef IPADDRINFO_H
#define IPADDRINFO_H
//==============IP地址信息===============

#include <QString>
#include <QList>

class IpAddrInfo
{
public:
    IpAddrInfo();
    IpAddrInfo(const QString &ipid,
               const QString &ipaddr,const QString &port);
    ~IpAddrInfo();

    void updataIpAddrInfo(IpAddrInfo *info);
    void updataIpAddrInfo(const QString &ipid,
                          const QString &ipaddr,const QString &port);

    void clearIpAddrInfo(void);

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void);

    void setIpID(const QString &ipid);
    const QString &getIpID(void) const;

    void setIpAddr(const QString &ipaddr);
    const QString &getIpAddr(void) const;

    void setPort(const QString &port);
    const QString &getPort(void) const;

private:
    QString m_IpID;     //ipid
    QString m_IpAddr;   //ip地址
    QString m_Port;     //端口
};

typedef QList<IpAddrInfo> List_IpAddrInfo;

#endif // IPADDRINFO_H
