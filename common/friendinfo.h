#ifndef FRIENDINFO_H
#define FRIENDINFO_H

#include "groupinfo.h"
#include "userinfo.h"

class FriendInfo : virtual public GroupInfo,virtual public UserInfo
{
public:
    FriendInfo();
    FriendInfo(const QString &fid, const QString &remark);
    ~FriendInfo();

    void updataFriendInfo(FriendInfo *info);
    void updataFriendInfo(const QString &fid, const QString &remark);

    void clearFriendInfo(void);

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void) const;

    const QString &getFID(void) const;
    void setFID(const QString &fid);

    const QString &getRemark(void) const;
    void setRemark(const QString &remark);

    private:
    QString m_fid;
    QString m_remark;
};
typedef QList<FriendInfo> List_FriendInfo;

#endif // FRIENTINFO_H
