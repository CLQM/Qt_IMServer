#ifndef PERSONINFO_H
#define PERSONINFO_H
//==============个人信息==============

#include <QString>
#include <QList>

class PersonInfo
{
public:
    PersonInfo();
    PersonInfo(const QString &pid, const QString &pname,
                const QString &sex,const QString &birth);
    ~PersonInfo();

    void updataPersoninfo(PersonInfo *info);        //更新
    void updataPersoninfo(const QString &pid, const QString &pname,
                          const QString &sex,const QString &birth);

    void clearPersoninfo(void);         //清除

    virtual void printInfos(void) const;    //打印
    virtual QString *packageinfo(void);     //可以添加到List<>

    void setPID(const QString &pid);
    const QString &getPID(void) const;

    void setPName(const QString &pname);
    const QString &getPName(void) const;

    void setPSex(const QString &sex);
    const QString &getPSex(void) const;

    void setPBirth(const QString &birth);
    const QString &getPBirth(void) const;

private:
    QString m_PID;     //sql PID
    QString m_PName;   //sql PName
    QString m_PSex;     //sql Sex
    QString m_PBirth;   //sql Birth
};

typedef QList<PersonInfo> List_PersonInfo;

#endif // PERSONINFO_H
