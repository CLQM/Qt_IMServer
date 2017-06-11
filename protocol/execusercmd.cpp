#include "execusercmd.h"

#include <QDebug>
#include <QStringList>
#include "sqlanalysis.h"

#include "listenclient.h"
#include "logfile.h"
#include "connectclient.h"

ExecUserCmd::ExecUserCmd()
{
    m_imProtocol = new IMProtocol;
}

ExecUserCmd::~ExecUserCmd()
{
    delete m_imProtocol;
}

void ExecUserCmd::analysisProtocol(IMProtocol *protocol)
{
    m_imProtocol->updataMsg(protocol);
//    m_imProtocol->printMsgInfo();

    execErrorInfo();
}

///
/// \brief ExecUserCmd::execErrorInfo
///
void ExecUserCmd::execErrorInfo(void)
{
    switch (m_imProtocol->getErrorInfo()) {
    case ERROR_INFO_NONE: execUserOperate(); break;
    case ERROR_INFO_DATA: break;
    case ERROR_INFO_BUSY: break;
    case ERROR_INFO_NETWORK: break;
    default: break;
    }
}

///
/// \brief ExecUserCmd::execUserOperate
///
void ExecUserCmd::execUserOperate(void)
{
    switch (m_imProtocol->getUserOperate()) {
    case USER_OPE_NONE: break;
    case USER_OPE_LOGIN: execOperateCmdLogin(); break;
    case USER_OPE_USER: execOperateCmdUser(); break;
    case USER_OPE_FRIEND: execOperateCmdFriend(); break;
    case USER_OPE_CROWD: execOperateCmdCrowd(); break;
    case USER_OPE_CHAT: execOperateCmdChat(); break;
    case USER_OPE_MOOD: execOperateCmdMood(); break;
    default: break;
    }
}

///
/// \brief ExecUserCmd::execOperateCmdLogin
///
void ExecUserCmd::execOperateCmdLogin(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_LOGIN_ASK: execOperateCmdLoginAsk(); break;
    case OPE_CMD_EXIT_ASK: execOperateCmdExitAsk(); break;
    case OPE_CMD_REGISTER_ASK: execOperateCmdRegisterAsk(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdLoginAsk(void)
{
    QStringList list = m_imProtocol->getDataContent().split("|");
    UserInfo *info = SQLAnalysis::selectUserInfo(list[0]);

    if(info->getRPassword() == list[1])
    {
        QString *msg = info->packageinfos();
        QByteArray *buffer =
                m_imProtocol->updataMsg(0, ERROR_INFO_NONE,
                                      USER_OPE_LOGIN, OPE_CMD_LOGIN_ASK,
                                      MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                      msg->size(), *msg);
        //W_INFO << "User Login Success";
        //添加在线列表
        info->updataIpAddrInfo(QString::number(SQLAnalysis::m_ipAddrInfoTotal)
                               ,list[2], list[3]);
        SQLAnalysis::insertIpAddrInfo(list[2], list[3]);
        ListenClient::m_userInfoList->append(*info);

        emit signalSendMsgtoClient(buffer);
    }else
    {
        QByteArray *buffer =
                m_imProtocol->updataMsg(0, ERROR_INFO_DATA,
                                      USER_OPE_LOGIN, OPE_CMD_LOGIN_ASK,
                                      MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                      MSG_DATA_LENGTH_NONE, NULL);

        emit signalSendMsgtoClient(buffer);
    }
}

void ExecUserCmd::execOperateCmdExitAsk(void)
{
}

void ExecUserCmd::execOperateCmdRegisterAsk(void)
{
    QStringList list = m_imProtocol->getDataContent().split("|");

    if(SQLAnalysis::insertRegisterInfo(list[0], list[1]))
    {
        if(SQLAnalysis::insertUserInfo(SQLAnalysis::m_registerUserTotal))
        {
            UserInfo *info = SQLAnalysis::selectUserInfo(
                        QString::number(SQLAnalysis::m_currentUserTotal));
            QString *msg = info->packageinfos();
            QByteArray *buffer =
                    m_imProtocol->updataMsg(0, ERROR_INFO_NONE,
                                          USER_OPE_LOGIN, OPE_CMD_REGISTER_ASK,
                                          MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                          MSG_DATA_LENGTH_NONE, *msg);
            emit signalSendMsgtoClient(buffer);
        }
    }
}

///
/// \brief ExecUserCmd::execOperateCmdUser
///
void ExecUserCmd::execOperateCmdUser(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_USER_ASK: execOperateCmdUserAsk(); break;
    case OPE_CMD_USER_DELETE: execOperateCmdUserUpdate(); break;
    case OPE_CMD_USER_UPDATE: execOperateCmdUserDelete(); break;
    case OPE_CMD_USER_CROWD_ASK: execOperateCmdUserCrowdAsk();break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdUserCrowdAsk(void)
{//群列表请求
    QString uid = m_imProtocol->getDataContent();
    List_CrowdInfo *clist = SQLAnalysis::selectCrowdInfoList(uid);
    QString msg;
    msg.clear();
    for(int  i = 0; i < clist->size(); i++)
    {
        msg += *(clist->at(i).packageinfos());
        msg += "^^";
    }
    QByteArray *buffer =
            m_imProtocol->updataMsg(0,ERROR_INFO_NONE,
                                    USER_OPE_USER,OPE_CMD_USER_CROWD_ASK,
                                    MSG_USER_HOST_NONE,MSG_USER_HOST_NONE,
                                    msg.size(),msg);
    emit signalSendMsgtoClient(buffer);

}


void ExecUserCmd::execOperateCmdUserAsk(void)
{//好友列表请求
    QString uid = m_imProtocol->getDataContent();
    List_FriendInfo *flist = new List_FriendInfo;
    List_GroupInfo *glist = SQLAnalysis::selectGroupInfoList(uid);
    for(int i = 0; i < glist->size(); i++)
    {
        List_FriendInfo *list =
                SQLAnalysis::selectFriendsInfoList(glist->at(i).getGID());
        for(int j = 0; j < list->size(); j++)
        {
            flist->append(list->at(j));
        }
    }

    QString msg;
    msg.clear();
    for(int i = 0; i < flist->size(); i++)
    {
        msg += *(flist->at(i).packageinfos());
        msg += "^^";
    }
    QByteArray *buffer =
            m_imProtocol->updataMsg(0, ERROR_INFO_NONE,
                                  USER_OPE_USER, OPE_CMD_USER_ASK,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg.size(), msg);

    emit signalSendMsgtoClient(buffer);
}

void ExecUserCmd::execOperateCmdUserUpdate(void)
{

}

void ExecUserCmd::execOperateCmdUserDelete(void)
{

}


///
/// \brief ExecUserCmd::execOperateCmdFriend
///
void ExecUserCmd::execOperateCmdFriend(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_FRIEND_ADD: execOperateCmdFriendAdd(); break;
    case OPE_CMD_FRIEND_ASK: execOperateCmdFriendAsk(); break;
    case OPE_CMD_FRIEND_DEL: execOperateCmdFriendDel(); break;
    case OPE_CMD_FRIEND_FIND: execOperateCmdFriendFind(); break;
    case OPE_CMD_FRIEND_REMARK: execOperateCmdFriendRemark(); break;
    case OPE_CMD_GROUP_ADD: execOperateCmdGroupAdd(); break;
    case OPE_CMD_GROUP_MODIFY: execOperateCmdGroupModify(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdFriendAsk(void)
{//添加好友请求
    QStringList list = m_imProtocol->getDataContent().split("|");
//    qDebug() << list;//2 6
    /*被添加 和 添加者*/
    UserInfo *recvinfo = SQLAnalysis::selectUserInfo(list.at(0));
    UserInfo *sendinfo = SQLAnalysis::selectUserInfo(list.at(1));


    for(int i = 0; i < ListenClient::m_userInfoList->size(); i++)
    {
        if(recvinfo->getUID() == ListenClient::m_userInfoList->at(i).getUID())
        {//漏洞
            QString *msg = sendinfo->packageinfos();
            QByteArray *buffer =
                    m_imProtocol->updataMsg(0, ERROR_INFO_NONE,
                                          USER_OPE_FRIEND, OPE_CMD_FRIEND_ASK,
                                          MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                          msg->size(), *msg);
//            qDebug() << list.at(0);
            emit signalSendAddFriendMsgtoClient(list.at(0),buffer);
            return;
        }
    }

    QString *msg = sendinfo->packageinfos();

//    qDebug() <<*msg;
    QByteArray *buffer =
            m_imProtocol->updataMsg(0, ERROR_INFO_DATA,
                                  USER_OPE_FRIEND, OPE_CMD_FRIEND_ASK,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg->size(), *msg);

    emit signalSendMsgtoClient(buffer);
}

void ExecUserCmd::execOperateCmdFriendFind(void)
{
    QString uid = m_imProtocol->getDataContent();

    UserInfo *info = SQLAnalysis::selectUserInfo(uid);
//    qDebug() << uid;
    if(!info->getUID().isEmpty())
    {
        QString *msg = info->packageinfos();
        info->printInfos();
        QByteArray *buffer =
                m_imProtocol->updataMsg(0, ERROR_INFO_NONE,
                                      USER_OPE_FRIEND, OPE_CMD_FRIEND_FIND,
                                      MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                      msg->size(), *msg);
//        qDebug() << *msg;
        emit signalSendMsgtoClient(buffer);
    }else
    {
        QByteArray *buffer =
                m_imProtocol->updataMsg(0, ERROR_INFO_DATA,
                                      USER_OPE_FRIEND, OPE_CMD_FRIEND_FIND,
                                      MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                      MSG_DATA_LENGTH_NONE, NULL);

        emit signalSendMsgtoClient(buffer);
    }
}

void ExecUserCmd::execOperateCmdFriendAdd(void)
{//同意好友申请
//    qDebug() << "同意添加";
    QStringList list = m_imProtocol->getDataContent().split("|");
    /*list0 添加者*/
    if(SQLAnalysis::insertFriendInfo(list[1],list[0]))
    {
        if(SQLAnalysis::insertFriendInfo(list[0],list[1]))
        {
//            qDebug() << "添加成功";
            execOperateCmdUserAsk();    //更新列表
        }
    }
}

void ExecUserCmd::execOperateCmdFriendDel(void)
{

}

void ExecUserCmd::execOperateCmdFriendRemark(void)
{

}

void ExecUserCmd::execOperateCmdGroupAdd(void)
{

}

void ExecUserCmd::execOperateCmdGroupModify(void)
{

}

///
/// \brief execOperateCmdCrowd
///
void ExecUserCmd::execOperateCmdCrowd(void)
{
//    qDebug() << "群组操作";
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_CROWD_ASK: execOperateCmdCrowdAsk(); break;
    case OPE_CMD_CROWD_UPDATE: execOperateCmdCrowdUpdate(); break;
    case OPE_CMD_CROWD_DEL: execOperateCmdCrowdDel(); break;
    case OPE_CMD_CROWD_ADD: execOperateCmdCrowdAdd(); break;
    case OPE_CMD_MEMBER_ADD: execOperateCmdMemberAdd(); break;
    case OPE_CMD_MEMBER_DEL: execOperateCmdMemberDel(); break;

    default: break;
    }
}


void ExecUserCmd::execOperateCmdCrowdAsk(void)
{

}

void ExecUserCmd::execOperateCmdCrowdUpdate(void)
{

}

void ExecUserCmd::execOperateCmdCrowdDel(void)
{

}

void ExecUserCmd::execOperateCmdCrowdAdd(void)
{

}

void ExecUserCmd::execOperateCmdMemberAdd(void)
{

}

void ExecUserCmd::execOperateCmdMemberDel(void)
{

}

///
/// \brief execOperateCmdChat
///
void ExecUserCmd::execOperateCmdChat(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_CHAT_PRIVATE: execOperateCmdChatPrivate(); break;
    case OPE_CMD_CHAT_CROWD: execOperateCmdChatCrowd(); break;
    case OPE_CMD_CHAT_RECALL: execOperateCmdChatRecall(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdChatPrivate(void)
{
    UserInfo *recvHost = SQLAnalysis::selectUserInfo(
                QString::number(m_imProtocol->getRecvHost()));
    UserInfo *sendHost = SQLAnalysis::selectUserInfo(
                QString::number(m_imProtocol->getSendHost()));
    emit signalRecordChatInfo(*recvHost, *sendHost, m_imProtocol->getDataContent());
}

void ExecUserCmd::execOperateCmdChatCrowd(void)
{

}

void ExecUserCmd::execOperateCmdChatRecall(void)
{

}

///
/// \brief execOperateCmdMood
///
void ExecUserCmd::execOperateCmdMood(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_MOOD_ASK: execOperateCmdMoodAsk(); break;
    case OPE_CMD_MOOD_FRIEND: execOperateCmdMoodFriend(); break;
    case OPE_CMD_MOOD_ADD: execOperateCmdMoodAdd(); break;
    case OPE_CMD_MOOD_DEL: execOperateCmdMoodDel(); break;
    case OPE_CMD_MOOD_FAVOUR: execOperateCmdMoodFavour(); break;
    case OPE_CMD_MOOD_NOTIFY: execOperateCmdMoodNotify(); break;
    case OPE_CMD_MOOD_REVIEW: execOperateCmdMoodReview(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdMoodAsk(void)
{

}

void ExecUserCmd::execOperateCmdMoodFriend(void)
{

}

void ExecUserCmd::execOperateCmdMoodAdd(void)
{

}

void ExecUserCmd::execOperateCmdMoodDel(void)
{

}

void ExecUserCmd::execOperateCmdMoodFavour(void)
{

}

void ExecUserCmd::execOperateCmdMoodNotify(void)
{

}

void ExecUserCmd::execOperateCmdMoodReview(void)
{

}
