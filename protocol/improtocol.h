#ifndef IMPROTOCOL_H
#define IMPROTOCOL_H

#include <QByteArray>
#include <QString>
#include <qmath.h>

#define MSG_USER_ID_NONE 0
#define MSG_USER_HOST_NONE 0
#define MSG_CMD_NULL_NONE 0
#define MSG_DATA_LENGTH_NONE 0

/*错误信息定义*/
enum ERROR_INFO{
    ERROR_INFO_NONE = 0,
    ERROR_INFO_DATA,
    ERROR_INFO_BUSY,
    ERROR_INFO_NETWORK
};

/*用户操作定义*/
enum USER_OPE{
    USER_OPE_NONE = 0,
    USER_OPE_LOGIN,
    USER_OPE_USER,
    USER_OPE_FRIEND,
    USER_OPE_CROWD,
    USER_OPE_CHAT,
    USER_OPE_MOOD
};

/*操作命令定义*/
enum OPE_CMD_LOGIN{
    OPE_CMD_LOGIN_ASK = 1,
    OPE_CMD_EXIT_ASK,
    OPE_CMD_REGISTER_ASK,
    OPE_CMD_REGISTER_ASK_NUM
};//添加帐号信息

enum OPE_CMD_USER{
    OPE_CMD_USER_ASK = 1,
    OPE_CMD_USER_UPDATE,
    OPE_CMD_USER_DELETE,
    OPE_CMD_USER_CROWD_ASK
};

enum OPE_CMD_FRIEND{
    OPE_CMD_FRIEND_ASK = 1,
    OPE_CMD_FRIEND_FIND,
    OPE_CMD_FRIEND_ADD,
    OPE_CMD_FRIEND_DEL,
    OPE_CMD_FRIEND_REMARK,
    OPE_CMD_GROUP_ADD,
    OPE_CMD_GROUP_MODIFY
};

enum OPE_CMD_CROWD{
    OPE_CMD_CROWD_ASK = 1,
    OPE_CMD_CROWD_UPDATE,
    OPE_CMD_CROWD_DEL,
    OPE_CMD_CROWD_ADD,
    OPE_CMD_MEMBER_ADD,
    OPE_CMD_MEMBER_DEL,
};

enum OPE_CMD_CHAT{
    OPE_CMD_CHAT_PRIVATE = 1,
    OPE_CMD_CHAT_CROWD,
    OPE_CMD_CHAT_RECALL
};

enum OPE_CMD_MOOD{
    OPE_CMD_MOOD_ASK = 1,
    OPE_CMD_MOOD_FRIEND,
    OPE_CMD_MOOD_ADD,
    OPE_CMD_MOOD_DEL,
    OPE_CMD_MOOD_FAVOUR,
    OPE_CMD_MOOD_NOTIFY,
    OPE_CMD_MOOD_REVIEW
};


class IMProtocol
{
public:
    IMProtocol();
    ~IMProtocol();

    bool initMsgPackage(void);  //初始化
    bool clearMsgPackage(void); //清除消息

    void printMsgInfo(void);    //打印相关消息
    void updataMsg(IMProtocol *protocol);   //更新消息
    QByteArray *updataMsg(const quint32 msgid, const quint8 errorinfo,
                          const quint8 useroperate, const quint8 operatecmd,
                          const quint16 recvhost, const quint16 sendhost,
                          const quint16 datalength, const QString datacontent);
    QByteArray *packageMsg(void);

    void unpackageMsg(QDataStream &in);

    quint32 getMsgID(void) const;
    void setMsgID(const quint32 msgid);
    quint8 getErrorInfo(void) const;
    void setErrorInfo(const quint8 errorinfo);
    quint8 getUserOperate(void) const;
    void setUserOperate(const quint8 useroperate);
    quint8 getOperateCmd(void) const;
    void setOperateCmd(const quint8 operatecmd);
    quint16 getRecvHost(void) const;
    void setRecvHost(const quint16 recvhost);
    quint16 getSendHost(void) const;
    void setSendHost(const quint16 sendhost);
    quint16 getDataLength(void) const;
    void setDataLength(const quint16 datalength);
    const QString &getDataContent(void) const;
    void setDataContent(const QString dataContent);

private:
    /*protocol detail*/
    quint32 m_MsgID;
    quint8 m_ErrorInfo;
    quint8 m_UserOperate;
    quint8 m_OperateCmd;
    quint16 m_RecvHost;
    quint16 m_SendHost;
    quint16 m_DataLength;
    QString m_DataContent;

};

#endif // IMPROTOCOL_H
