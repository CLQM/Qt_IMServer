#include "personinfo.h"
#include <QDebug>

PersonInfo::PersonInfo()
{
}

PersonInfo::PersonInfo(const QString &pid, const QString &pname,
                       const QString &sex, const QString &birth)
{
    updataPersoninfo(pid,pname,sex,birth);
}

PersonInfo::~PersonInfo()
{
}

void PersonInfo::updataPersoninfo(const QString &pid, const QString &pname,
                                  const QString &sex, const QString &birth)
{
    m_PID = pid;
    m_PName = pname;
    m_PSex = sex;
    m_PBirth = birth;
}

void PersonInfo::updataPersoninfo(PersonInfo *info)
{
    m_PID = info->getPID();
    m_PName = info->getPName();
    m_PSex = info->getPSex();
    m_PBirth = info->getPBirth();
}

void PersonInfo::clearPersoninfo()
{
    m_PID.clear();
    m_PName.clear();
    m_PSex.clear();
    m_PBirth.clear();
}

void PersonInfo::printInfos(void) const
{
    qDebug() << "=========personinfo======";
    qDebug() << "ID" << getPID();
    qDebug() << "Name" << getPName();
    qDebug() << "Sex" << getPSex();
    qDebug() << "Birth" << getPBirth();
    qDebug() << "=========personinfo======";
}

QString *PersonInfo::packageinfo(void)
{
    QString *data = new QString();
    data->clear();

    data->append(getPID());
    data->append("|");
    data->append(getPName());
    data->append("|");
    data->append(getPSex());
    data->append("|");
    data->append(getPBirth());

    return data;
}

void PersonInfo::setPID(const QString &pid)
{
    m_PID = pid;
}

const QString &PersonInfo::getPID(void) const
{
     return m_PID;
}

void PersonInfo::setPName(const QString &pname)
{
    m_PName = pname;
}

const QString &PersonInfo::getPName(void) const
{
    return m_PName;
}

void PersonInfo::setPSex(const QString &sex)
{
    m_PSex = sex;
}

const QString &PersonInfo::getPSex(void) const
{
    return m_PSex;
}

void PersonInfo::setPBirth(const QString &birth)
{
    m_PBirth = birth;
}

const QString &PersonInfo::getPBirth() const
{
    return m_PBirth;
}
