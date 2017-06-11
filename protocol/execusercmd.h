#ifndef EXECUSERCMD_H
#define EXECUSERCMD_H
//===========用户操作信息
#include <QObject>
#include <QDebug>

#include "improtocol.h"
#include "common.h"
#include "friendinfo.h"
#include "groupinfo.h"
#include "crowdinfo.h"

class ExecUserCmd : public QObject
{
    Q_OBJECT
public:
    ExecUserCmd();
    ~ExecUserCmd();
    void execErrorInfo(void);
    void analysisProtocol(IMProtocol *protocol);    //分析
    void execUserOperate(void);     //
    void execOperateCmdLogin(void);
    void execOperateCmdUser(void);
    void execOperateCmdFriend(void);
    void execOperateCmdCrowd(void);
    void execOperateCmdChat(void);
    void execOperateCmdMood(void);

    void execOperateCmdLoginAsk(void);
    void execOperateCmdExitAsk(void);
    void execOperateCmdRegisterAsk(void);

    void execOperateCmdUserAsk(void);
    void execOperateCmdUserDelete(void);
    void execOperateCmdUserUpdate(void);
    void execOperateCmdUserCrowdAsk(void);

    void execOperateCmdFriendAdd(void);
    void execOperateCmdFriendAsk(void);
    void execOperateCmdFriendDel(void);
    void execOperateCmdFriendFind(void);
    void execOperateCmdFriendRemark(void);

    void execOperateCmdGroupAdd(void);
    void execOperateCmdGroupModify(void);

    void execOperateCmdCrowdAsk(void);
    void execOperateCmdCrowdUpdate(void);
    void execOperateCmdCrowdDel(void);
    void execOperateCmdCrowdAdd(void);
    void execOperateCmdMemberAdd(void);
    void execOperateCmdMemberDel(void);

    void execOperateCmdChatPrivate(void);
    void execOperateCmdChatCrowd(void);
    void execOperateCmdChatRecall(void);

    void execOperateCmdMoodAsk(void);
    void execOperateCmdMoodFriend(void);
    void execOperateCmdMoodAdd(void);
    void execOperateCmdMoodDel(void);
    void execOperateCmdMoodFavour(void);
    void execOperateCmdMoodNotify(void);
    void execOperateCmdMoodReview(void);

    void execOperateCmdNum(void);

signals:
    void signalSendMsgtoClient(QByteArray *buffer);
    void signalRecordChatInfo(const UserInfo &recvUser,
                              const UserInfo &sendUser,
                              const QString &msg);
    void signalSendAddFriendMsgtoClient(QString id ,QByteArray *buffer);
public slots:

private:
    IMProtocol *m_imProtocol;
};

#endif // EXECUSERCMD_H
