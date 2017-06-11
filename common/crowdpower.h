#ifndef CROWDPOWER_H
#define CROWDPOWER_H


#include <QString>

class CrowdPower
{
public:
    CrowdPower();
    CrowdPower(const QString &powerid,
               const QString &userpower,const QString &powerdescribe);
    ~CrowdPower();

    void updataCrowdPower(CrowdPower *power);
    void updataCrowdPower(const QString &powerid,
                          const QString &userpower,const QString &powerdescribe);
    void clearCrowdPower();

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void);

    const QString &getPowerID(void) const;
    void setPowerID(const QString &powerid);

    const QString &getUserPower(void) const;
    void setUserPower(const QString &userpower);

    const QString &getPowerDescribe(void) const;
    void setPowerDescribe(const QString &powerdescribe);

private:
    QString m_PowerID;
    QString m_UserPower;
    QString m_PowerDescribe;

};

#endif // CROWDPOWER_H
