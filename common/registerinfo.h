#ifndef REGISTERINFO_H
#define REGISTERINFO_H
//=================注册信息===============

#include <QString>
#include <QList>

class RegisterInfo
{//
public:
    RegisterInfo();
    RegisterInfo(const QString &rid,const QString &name,
                 const QString &password,const QString &time);
    ~RegisterInfo();

    void updataRegisterInfo(RegisterInfo *info);        //赋值函数
    void updataRegisterInfo(const QString &rid,const QString &name,
                            const QString &password,const QString &time);

    void clearRegisterInfo(void);   //清除此注册用户

    virtual void printInfos(void) const;         //打印本用户的info
    virtual QString *packageinfos(void);

    void setRID(const QString &pid);        //sql RID
    const QString &getRID(void) const;

    void setRName(const QString &name);    //sql RName
    const QString &getRName(void) const;

    void setRPassword(const QString &password);        //sql RPassword
    const QString &getRPassword(void) const;

    void setRTime(const QString &time);  //sql RTime
    const QString &getRTime(void) const;

private:
    QString m_RID;         //ID
    QString m_RName;       //name
    QString m_RPassword;    //password
    QString m_RTime;       //register Time
};

typedef QList<RegisterInfo> List_RegisterInfo;

#endif // REGISTERINFO_H
