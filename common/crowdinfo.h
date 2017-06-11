#ifndef CROWDINFO_H
#define CROWDINFO_H

#include "userinfo.h"
#include "crowdpower.h"

#include <QList>

class CrowdInfo : public UserInfo ,public CrowdPower
{
public:
    CrowdInfo();
    CrowdInfo(const QString &cid,const QString &cname,const QString &cintro);
    ~CrowdInfo();

    void updataCrowdInfo(CrowdInfo *info);
    void updataCrowdInfo(const QString &cid,const QString &cname,const QString &cintro);

    void clearCrowdInfo(void);

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void) const;

    const QString &getCID(void) const;
    void setCID(const QString &cid);

    const QString &getCName(void) const;
    void setCName(const QString &cname);

    const QString &getCIntro(void) const;
    void setCIntro(const QString &cintro);

private:
    QString m_CID;
    QString m_CName;
    QString m_CIntro;
};

typedef QList<CrowdInfo> List_CrowdInfo;

#endif // CROWDINFO_H
