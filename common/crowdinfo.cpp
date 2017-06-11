#include "crowdinfo.h"

#include <QDebug>

CrowdInfo::CrowdInfo()
{

}

CrowdInfo::CrowdInfo(const QString &cid,
                     const QString &cname,const QString &cintro)
{
    updataCrowdInfo(cid,cname,cintro);
}

CrowdInfo::~CrowdInfo()
{}

void CrowdInfo::updataCrowdInfo(CrowdInfo *info)
{
    m_CID = info->getCID();
    m_CName = info->getCName();
    m_CIntro = info->getCIntro();
}

void CrowdInfo::updataCrowdInfo(const QString &cid,
                                const QString &cname,const QString &cintro)
{
    m_CID = cid;
    m_CName = cname;
    m_CIntro = cintro;
}

void CrowdInfo::clearCrowdInfo(void)
{
    m_CID.clear();
    m_CName.clear();
    m_CIntro.clear();
}

void CrowdInfo::printInfos(void) const
{
    qDebug() << "CrowdInfo---------------";
    qDebug() << getCID();
    qDebug() << getCName();
    qDebug() << getCIntro();
    qDebug() << "CrowdInfo---------------";
}

QString *CrowdInfo::packageinfos(void) const
{
    QString *data = new QString();
    data->clear();

    data->append(getCID());
    data->append("|");
    data->append(getCName());
    data->append("|");
    data->append(getCIntro());

}

const QString &CrowdInfo::getCID(void) const
{
    return m_CID;
}

void CrowdInfo::setCID(const QString &cid)
{
    m_CID = cid;
}

const QString &CrowdInfo::getCName(void) const
{
    return m_CName;
}
void CrowdInfo::setCName(const QString &cname)
{
    m_CName = cname;
}

const QString &CrowdInfo::getCIntro(void) const
{
    return m_CIntro;
}

void CrowdInfo::setCIntro(const QString &cintro)
{
    m_CIntro = cintro;
}
