#ifndef USERINFO_H
#define USERINFO_H
//=================用户信息=====================
#include <QString>
#include <QList>
#include "common.h"


class UserInfo : public RegisterInfo ,public IpAddrInfo,public StatuInfo
{
public:
    UserInfo();
    UserInfo(const QString &uid, const QString &selfsign);
    ~UserInfo();

    void updataUserInfo(UserInfo *info);
    void updataUserInfo(const QString &uid,
                        const QString &selfsign);

    void clearUserInfo(void);

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void);

    const QString &getUID(void) const;
    void setUID(const QString &uid);

    const QString &getSelfSign(void) const;
    void setSelfSign(const QString &selfsign);

private:
    QString m_UID;
    QString m_SelfSign;
};

typedef QList<UserInfo> List_UserInfo;

#endif // USERINFO_H
