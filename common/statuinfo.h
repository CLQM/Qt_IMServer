#ifndef STATUINFO_H
#define STATUINFO_H
//=================状态信息===============

#include <QString>
#include <QList>

class StatuInfo
{
public:
    StatuInfo();
    StatuInfo(const QString &sid,const QString &sname,
              const QString &sicon);
    ~StatuInfo();

    void updataStatuinfo(StatuInfo *info);
    void updataStatuinfo(const QString &sid,const QString &sname,
                         const QString &sicon);
    void clearStatuinfo(void);

    virtual void printInfos(void)const;
    virtual QString *packageinfos(void);

    void setSID(const QString &sid);
    const QString &getSID(void)const;

    void setSName(const QString &sname);
    const QString &getSName(void)const;

    void setSIcon(const QString &sicon);
    const QString &getSIcon(void)const;

private:
    QString m_SID;          //状态id
    QString m_SName;        //statu name
    QString m_SIcon;        //statu icon
};

typedef QList<StatuInfo> List_StatuInfo;

#endif // STATUINFO_H
