#ifndef GROUPINFO_H
#define GROUPINFO_H

#include "userinfo.h"

#include <QString>
#include <QList>


class GroupInfo : virtual public UserInfo
{
public:
    GroupInfo();
    GroupInfo(const QString &gid, const QString &gname);
    ~GroupInfo();

    void updataGroupInfo(GroupInfo *info);
    void updataGroupInfo(const QString &gid, const QString &gname);

    void clearGroupInfo(void);

    void printInfos(void) const;
    virtual QString *packageinfos(void);

    const QString &getGID(void) const;
        void setGID(const QString &gid);

        const QString &getGName(void) const;
        void setGName(const QString &gname);

    private:
        QString m_gid;
        QString m_gname;
};

typedef QList<GroupInfo> List_GroupInfo;

#endif // GROUPINFO_H
