#include "crowdpower.h"

#include <QDebug>

CrowdPower::CrowdPower()
{}

CrowdPower::CrowdPower(const QString &powerid,
           const QString &userpower,const QString &powerdescribe)
{
    updataCrowdPower(powerid,userpower,powerdescribe);
}

CrowdPower::~CrowdPower()
{}

void CrowdPower::updataCrowdPower(CrowdPower *power)
{
    m_PowerID = power->getPowerID();
    m_UserPower = power->getUserPower();
    m_PowerDescribe = power->getPowerDescribe();
}

void CrowdPower::updataCrowdPower(const QString &powerid,
                      const QString &userpower,const QString &powerdescribe)
{
    m_PowerID = powerid;
    m_PowerDescribe = powerdescribe;
    m_UserPower = userpower;
}

void CrowdPower::clearCrowdPower()
{
    m_PowerID.clear();
    m_UserPower.clear();
    m_PowerDescribe.clear();
}

 void CrowdPower::printInfos(void) const
{
    qDebug() << "Crowdpower-----------------";
    qDebug() << getPowerID();
    qDebug() << getUserPower();
    qDebug() << getPowerDescribe();
    qDebug() << "Crowdpower-----------------";
}
QString *CrowdPower::packageinfos(void)
{
    QString *data = new QString;
    data->clear();

    data->append(getPowerID());
    data->append("|");
    data->append(getUserPower());
    data->append("|");
    data->append(getPowerDescribe());

    return data;
}

const QString &CrowdPower::getPowerID(void) const
{
    return m_PowerID;
}

void CrowdPower::setPowerID(const QString &powerid)
{
    m_PowerID = powerid;
}

const QString &CrowdPower::getUserPower(void) const
{
    return m_UserPower;
}

void CrowdPower::setUserPower(const QString &userpower)
{
    m_UserPower = userpower;
}

const QString &CrowdPower::getPowerDescribe(void) const
{
    return m_PowerDescribe;
}

void CrowdPower::setPowerDescribe(const QString &powerdescribe)
{
    m_PowerDescribe = powerdescribe;
}


