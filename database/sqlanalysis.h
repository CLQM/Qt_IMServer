#ifndef SQLANALYSIS_H
#define SQLANALYSIS_H
//=============sql相关操作===============

#include "common.h"
#include "groupinfo.h"
#include "friendinfo.h"
#include "crowdinfo.h"

class SQLAnalysis
{
public:
    SQLAnalysis();

    static PersonInfo *selectPersonInfo(QString id);

    static void getTotalRegisterUser(void);
    static RegisterInfo *selectRegisterInfo(QString id);
    static bool insertRegisterInfo(QString name, QString pswd);
    static bool updateRegisterInfo(QString rid,QString name);

    static void getTotalIpAddrInfo(void);
    static IpAddrInfo *selectIpAddrInfo(QString id);
    static bool insertIpAddrInfo(QString ipAddr,QString port);

    static void getTotalCurrentUser(void);
    static UserInfo *selectUserInfo(QString id);
    static bool insertUserInfo(quint32 rid);
    static bool updateUserInfo( QString uid,QString sign);

    static bool getTotalFriendInfo(void);
    static bool insertFriendInfo(QString recv,QString send);

    static List_GroupInfo *selectGroupInfoList(QString id);

    ///
    /// \brief selectGroupInfo
    /// \param id
    /// \return
    ///
    static FriendInfo *selectFriendsInfo(QString id);
    static List_FriendInfo *selectFriendsInfoList(QString id);

    static CrowdPower *selectCrowdPower(QString id);

    static CrowdInfo *selectCrowdInfo(QString id);
    static List_CrowdInfo *selectCrowdInfoList(QString id);
    static bool getTotalCrowdMember(void);

    static quint32 m_ipAddrInfoTotal;
    static quint32 m_registerUserTotal;
    static quint32 m_currentUserTotal;
    static quint32 m_friendInfoTotal;

    static quint32 m_crowdMemberTotal;
    static quint32 m_registerUserNum;
};

#endif // SQLANALYSIS_H
