#include "sqlanalysis.h"

#include <QSqlQuery>
#include <QString>
#include <QDateTime>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlQuery>

quint32 SQLAnalysis::m_ipAddrInfoTotal = 0;
quint32 SQLAnalysis::m_registerUserTotal = 0;
quint32 SQLAnalysis::m_currentUserTotal = 0;
quint32 SQLAnalysis::m_registerUserNum = 0;
quint32 SQLAnalysis::m_friendInfoTotal = 0;
quint32 SQLAnalysis::m_crowdMemberTotal = 0;

SQLAnalysis::SQLAnalysis()
{
    getTotalCurrentUser();
    getTotalIpAddrInfo();
    getTotalRegisterUser();
    getTotalCrowdMember();
}

PersonInfo *SQLAnalysis::selectPersonInfo(QString id)
{
    PersonInfo *info = new PersonInfo;
    QSqlQuery query;    //嵌入式sql，在qt中执行sql
    //基础语句
    QString basicString = QString("select * from PersonInfoTable "
                                  "whele PersonInfoTable.ID='%1'");
    QString queryString = basicString.arg(id);  //查询结果赋值给querystring

    if(query.exec(queryString))
    {//执行搜索
        int id_idx = query.record().indexOf("PID");
        //QSqlQuery.QSqlRecord.int 返回字段PID的索引
        int name_idx = query.record().indexOf("PName");
        int sex_idx = query.record().indexOf("PSex");
        int birth_idx = query.record().indexOf("PBirth");

        while(query.next())
        {//搜索结果
            QString id = query.value(id_idx).toString();        //QSqlQuery.QVariant.QString
            QString name = query.value(name_idx).toString();
            QString sex = query.value(sex_idx).toString();
            QString birth = query.value(birth_idx).toString();

            info->updataPersoninfo(id,name,sex,birth);
        }
    }
    return info;
}

bool SQLAnalysis::updateRegisterInfo(QString rid, QString name)
{
    QSqlQuery query;
    QString basicString = QString("update registerinfotable set RName = '%1' where RID = '%2'");
    QString queryString = basicString.arg(name).arg(rid);
    return query.exec(queryString);
}



void SQLAnalysis::getTotalRegisterUser(void)
{//计算总数
    m_registerUserTotal = 0;

    QSqlQuery query;        //QT中实现嵌入式sql的类
    QString queryString = QString("select * from RegisterInfoTable");

    if(query.exec(queryString))
    {
        int id_idx = query.record().indexOf("RID"); //作一个RID的标识

        while(query.next())
        {
            QString id = query.value(id_idx).toString();
            m_registerUserTotal++;
        }
    }
}

RegisterInfo *SQLAnalysis::selectRegisterInfo(QString id)
{
    RegisterInfo *info = new RegisterInfo;
    QSqlQuery query;    //qt中实现嵌入式sql的类

    QString basicString = QString("select * from RegisterInfoTable "
                                  "where RegisterInfoTable.RID = '%1'");
    QString queryString = basicString.arg(id);  //完整语句

    if(query.exec(queryString))
    {//查询
        int id_idx = query.record().indexOf("RID");     //索引
        int name_idx = query.record().indexOf("RName");
        int pswd_idx = query.record().indexOf("RPassword");
        int time_idx = query.record().indexOf("RTime");

        while (query.next())
        {
            QString id = query.value(id_idx).toString();    //借助索引获得信息
            QString name = query.value(name_idx).toString();
            QString pswd = query.value(pswd_idx).toString();
            QString time = query.value(time_idx).toString();

            info->updataRegisterInfo(id, name, pswd, time); //updata
        }
    }
    return info;
}

bool SQLAnalysis::insertRegisterInfo(QString name, QString pswd)
{//当有新注册的用户时调用
    getTotalRegisterUser();     //统计
    QSqlQuery query;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    //获得系统当前时间，转为string
    QString basicString = QString("insert into RegisterInfoTable values('%1', '%2', '%3', '%4')");
    QString queryString = basicString.arg(++m_registerUserTotal)
            .arg(name).arg(pswd).arg(time);     //完整语句
    qDebug() << "insertRegisterInfo";
    return query.exec(queryString); //执行
}

void SQLAnalysis::getTotalIpAddrInfo(void)
{//计算总数
    m_ipAddrInfoTotal = 0;  //置0

    QSqlQuery query;        //QT中实现嵌入式sql的类
    QString queryString = QString("select * from IpAddrInfoTable");

    if(query.exec(queryString))
    {
        int ipid_idx = query.record().indexOf("IpID");    //作一个IpID的标识
        while(query.next())
        {
            QString ipid = query.value(ipid_idx).toString();
            m_ipAddrInfoTotal++;
        }
    }
}
bool SQLAnalysis::insertIpAddrInfo(QString ipAddr, QString port)
{//插入元组
    getTotalIpAddrInfo();   //求总
    QSqlQuery query;    //嵌入式sql
    QString basicString = QString("insert into IpAddrInfoTable values("
                          "'%1','%2','%3')");
    QString queryString = basicString.arg(++m_registerUserTotal).arg(ipAddr).arg(port);

    return query.exec(queryString);
}

IpAddrInfo *SQLAnalysis::selectIpAddrInfo(QString id)
{
    IpAddrInfo *info = new IpAddrInfo;
    QSqlQuery query;    //qt中实现嵌入式sql的类

    QString basicString = QString("select * from IpAddrInfoTable "
                                  "where IpAddrInfoTable.IpID='%1'");
    QString queryString = basicString.arg(id); //完整语句
    if(query.exec(queryString))
    {//查询
        int ipid_idx = query.record().indexOf("IpID");
        int ipaddr_idx = query.record().indexOf("IpAddr");
        int port_idx = query.record().indexOf("Port");

        while(query.next())
        {
            QString ipid = query.value(ipid_idx).toString();
            QString ipaddr = query.value(ipaddr_idx).toString();
            QString port = query.value(port_idx).toString();

            info->updataIpAddrInfo(ipid, ipaddr, port);
        }
    }
    return info;
}
void SQLAnalysis::getTotalCurrentUser(void)
{//计算总数
    m_currentUserTotal = 0;
    QSqlQuery query;
    QString queryString = QString("select * from UserInfoTable");

    if(query.exec(queryString))
    {
       int uid_idx = query.record().indexOf("UID");

       while (query.next())
       {
           QString uid = query.value(uid_idx).toString();
           m_currentUserTotal++;
       }
    }
}
UserInfo *SQLAnalysis::selectUserInfo(QString id)
{
    UserInfo *info =new UserInfo;
    QSqlQuery query;   //qt中实现嵌入式sql的lei

    QString basicString = QString("select * from UserInfoTable where UserInfoTable.UID='%1'");
    QString queryString = basicString.arg(id);

    if(query.exec(queryString))
    {//搜索
        int uid_idx = query.record().indexOf("UID");
        int rid_idx = query.record().indexOf("RID");
        int selfsign_idx = query.record().indexOf("SelfSign");
        int ipid_idx = query.record().indexOf("IpID");

        while(query.next())
        {
            QString uid = query.value(uid_idx).toString();
            QString rid = query.value(rid_idx).toString();
            QString selfsign = query.value(selfsign_idx).toString();
            QString ipid = query.value(ipid_idx).toString();

            info->updataUserInfo(uid, selfsign);
            info->updataIpAddrInfo(selectIpAddrInfo(ipid));
            info->updataRegisterInfo(selectRegisterInfo(rid));
        }
    }
    return info;
}

bool SQLAnalysis::updateUserInfo(QString uid, QString sign)
{
    QSqlQuery query;
    QString basicString = QString("update userinfotable set selfsign = '%1' where uid = '%2'");
    QString queryString = basicString.arg(sign).arg(uid);
    return query.exec(queryString);
}

bool SQLAnalysis::insertUserInfo(quint32 rid)
{
    getTotalCurrentUser();  //计算总数
    QSqlQuery query;        //嵌入式sql
    QString basicString = QString("insert into UserInfoTable values('%1','%2',NULL,NULL,NULL,NULL,NULL)");
    QString queryString = basicString.arg(++m_currentUserTotal).arg(rid);

    return query.exec(queryString);
}

List_GroupInfo *SQLAnalysis::selectGroupInfoList(QString id)
{

    GroupInfo *info = new GroupInfo;
    List_GroupInfo *list = new List_GroupInfo;
    QSqlQuery query;
    QString basicString = QString("select * from GroupInfoTable where GroupInfoTable.GID='%1'");
    QString queryString = basicString.arg(id);

    if(query.exec(queryString))
    {
        qDebug() << "selectGroupInfoList";
        int gid_idx = query.record().indexOf("GID");
        int gname_idx = query.record().indexOf("GName");

        while(query.next())
        {
            QString gid = query.value(gid_idx).toString();
            QString gname = query.value(gname_idx).toString();

            info->updataGroupInfo(gid, gname);
            info->updataUserInfo(SQLAnalysis::selectUserInfo(id));
            list->append(*info);
        }
    }
    return list;
}

FriendInfo *SQLAnalysis::selectFriendsInfo(QString id)
{
    FriendInfo *info = new FriendInfo;

    QSqlQuery query;
    QString basicString = QString("select * from FriendInfoTable where FriendInfoTable.GID='%1'");
    QString queryString = basicString.arg(id);

    if(query.exec(queryString))
    {
        int fid_idx = query.record().indexOf("FID");
        int uid_idx = query.record().indexOf("UID");
        int remark_idx = query.record().indexOf("Remark");

        while (query.next())
        {
            QString fid = query.value(fid_idx).toString();
            QString uid = query.value(uid_idx).toString();
            QString remark = query.value(remark_idx).toString();

            info->updataFriendInfo(fid, remark);
            info->updataUserInfo(SQLAnalysis::selectUserInfo(uid));
        }
    }

    return info;
}

List_FriendInfo *SQLAnalysis::selectFriendsInfoList(QString id)
{
    FriendInfo *info = new FriendInfo;
    List_FriendInfo *list = new List_FriendInfo;

    QSqlQuery query;
    QString basicString = QString("select * from FriendInfoTable "
                                  "where FriendInfoTable.GID = '%1'");
    QString queryString = basicString.arg(id);

    if(query.exec(queryString))
    {
        int fid_idx = query.record().indexOf("FID");
        int uid_idx = query.record().indexOf("UID");
        int remark_idx = query.record().indexOf("Remark");

        while (query.next())
        {
            QString fid = query.value(fid_idx).toString();
            QString uid = query.value(uid_idx).toString();
            QString remark = query.value(remark_idx).toString();


            info->updataFriendInfo(fid, remark);
            info->updataUserInfo(SQLAnalysis::selectUserInfo(uid));
            list->append(*info);
        }
    }

    return list;
}

bool SQLAnalysis::getTotalFriendInfo(void)
{
    m_friendInfoTotal = 0;
    QSqlQuery query;
    QString queryString = QString("select * from FriendInfoTable");
    if(query.exec(queryString))
    {
        int fid_idx = query.record().indexOf("FID");
        while(query.next())
        {
            QString fid = query.value(fid_idx).toString();
            m_friendInfoTotal++;
        }
    }
}

bool SQLAnalysis::getTotalCrowdMember(void)
{
    m_crowdMemberTotal = 0;
    QSqlQuery query;
    QString queryString = QString("select * from CrowdMemberTable");
    if(query.exec(queryString))
    {
        int cid_idx = query.record().indexOf("CID");
        while(query.next())
        {
            QString cid = query.value(cid_idx).toString();
            m_crowdMemberTotal++;
        }
    }
}

CrowdPower *SQLAnalysis::selectCrowdPower(QString id)
{
    CrowdPower *power = new CrowdPower;
    QSqlQuery query;    //qt中实现嵌入式sql的类

    QString basicString = QString("select * from CrowdPowerTable "
                                  "where CrowdPowerTable.PowerID='%1'");
    QString queryString = basicString.arg(id); //完整语句
    if(query.exec(queryString))
    {//查询

        int powerid_idx = query.record().indexOf("PowerID");
        int userpower_idx = query.record().indexOf("UserPower");
        int powerdescribe_idx = query.record().indexOf("PowerDescribe");

        while(query.next())
        {
            QString powerid = query.value(powerid_idx).toString();
            QString userpower = query.value(userpower_idx).toString();
            QString powerdescibe = query.value(powerdescribe_idx).toString();

            power->updataCrowdPower(powerid,userpower,powerdescibe);
        }
    }
    return power;
}

CrowdInfo *SQLAnalysis::selectCrowdInfo(QString id)
{
    CrowdInfo *info = new CrowdInfo;

    QSqlQuery query;
    QString basicString = QString("select * from CrowdInfoTable where CrowdInfoTable.CID='%1'");
    QString queryString = basicString.arg(id);
    if(query.exec(queryString))
    {
        int cname_idx = query.record().indexOf("CName");
        int uid_idx = query.record().indexOf("UID");
        int cintro_idx = query.record().indexOf("CIntro");
        int powerid_idx = query.record().indexOf("PowerID");

        while(query.next())
        {
            QString cname = query.value(cname_idx).toString();
            QString uid = query.value(uid_idx).toString();
            QString cintro = query.value(cintro_idx).toString();
            QString powerid = query.value(powerid_idx).toString();

            info->updataCrowdInfo(id,cname,cintro);
            info->updataUserInfo(selectUserInfo(uid));
            info->updataCrowdPower(selectCrowdPower(powerid));
        }
    }
    return info;
}

List_CrowdInfo *SQLAnalysis::selectCrowdInfoList(QString id)
{
    CrowdInfo *info = new CrowdInfo;
    List_CrowdInfo *list = new List_CrowdInfo;

    QSqlQuery query;
    QString  basicString = QString("select * from CrowdMemberTable where "
                                   "CrowdMemberTable.UID = '%1'");
    QString queryString = basicString.arg(id);

    if(query.exec(queryString))
    {
        int cid_idx = query.record().indexOf("CID");

        while (query.next())
        {
            QString cid = query.value(cid_idx).toString();

            info->updataCrowdInfo(selectCrowdInfo(cid));
            list->append(*info);
        }
    }
    return list;
}

bool SQLAnalysis::insertFriendInfo(QString recv, QString send)
{//好友列表添加好友  //要添加两条信息
    getTotalFriendInfo();
    QSqlQuery query;
    QString basicString = QString("insert into FriendInfoTable values('%1','%2','%3',NULL)");
    QString queryString = basicString.arg(++m_friendInfoTotal).arg(recv).arg(send);
    QString queryString1 = basicString.arg(++m_friendInfoTotal).arg(send).arg(recv);

    qDebug() << basicString;
    qDebug() << queryString;
    qDebug() << queryString1;

    return query.exec(queryString) & query.exec(queryString1);
}
