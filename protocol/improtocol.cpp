#include "improtocol.h"

#include <QDataStream>  //二进制数据到QIODevice串行化
#include <QIODevice>
#include <QDebug>

IMProtocol::IMProtocol()
{
    initMsgPackage();
}

IMProtocol::~IMProtocol()
{

}

void IMProtocol::updataMsg(IMProtocol *protocol)
{
    m_MsgID = protocol->getMsgID();
    m_ErrorInfo = protocol->getErrorInfo();
    m_UserOperate= protocol->getUserOperate();
    m_OperateCmd = protocol->getOperateCmd();
    m_RecvHost = protocol->getRecvHost();
    m_SendHost = protocol->getSendHost();
    m_DataLength = protocol->getDataLength();
    m_DataContent = protocol->getDataContent();
}

QByteArray * IMProtocol::updataMsg(const quint32 msgid, const quint8 errorinfo,
                      const quint8 useroperate, const quint8 operatecmd,
                      const quint16 recvhost, const quint16 sendhost,
                      const quint16 datalength, const QString datacontent)
{//将相关信息给一个协议对象临时保存
    m_MsgID = msgid;
    m_ErrorInfo = errorinfo;
    m_UserOperate = useroperate;
    m_OperateCmd = operatecmd;
    m_RecvHost = recvhost;
    m_SendHost = sendhost;
    m_DataLength = datalength;
    m_DataContent = datacontent;

    return packageMsg();
}

QByteArray *IMProtocol::packageMsg(void)
{//将对象中的信息组装为可发送的QBytearray
    QByteArray *buffer =  new  QByteArray;
    QDataStream out(buffer,QIODevice::WriteOnly);//定义一个数据流，指向buffer
    out.setVersion(QDataStream::Qt_4_6);
    out << m_MsgID;
    out << m_ErrorInfo;
    out << m_UserOperate;
    out << m_OperateCmd;
    out << m_RecvHost;
    out << m_SendHost;
    out << m_DataLength;
    out << m_DataContent;

    return buffer;
}

bool IMProtocol::initMsgPackage(void)
{//初始化消息队列
    clearMsgPackage();
}

bool IMProtocol::clearMsgPackage()
{//清除已有信息
    m_MsgID = MSG_USER_ID_NONE;
    m_ErrorInfo = ERROR_INFO_NONE;
    m_UserOperate = USER_OPE_USER;
    m_OperateCmd =MSG_CMD_NULL_NONE;
    m_RecvHost = MSG_USER_HOST_NONE;
    m_SendHost = MSG_USER_HOST_NONE;
    m_DataLength = MSG_DATA_LENGTH_NONE;
    m_DataContent.clear();
    return true;
}


void IMProtocol::printMsgInfo(void)
{//打印当前信息
    qDebug() << "IMProtocol::printMsgInfo===============================";
    qDebug() << "IMProtocol::MsgID          :  " << m_MsgID;
    qDebug() << "IMProtocol::ErrorInfo      :  " << m_ErrorInfo;
    qDebug() << "IMProtocol::UserOperate    :  " << m_UserOperate;
    qDebug() << "IMProtocol::OperateCmd     :  " << m_OperateCmd;
    qDebug() << "IMProtocol::RecvHost       :  " << m_RecvHost;
    qDebug() << "IMProtocol::SendHost       :  " << m_SendHost;
    qDebug() << "IMProtocol::DataLength     :  " << m_DataLength;
    qDebug() << "IMProtocol::DataContent    :  " << m_DataContent;
    qDebug() << "IMProtocol::printMsgInfo===============================";
}
void IMProtocol::unpackageMsg(QDataStream &in)
{//由套接字读信息
    in >> m_MsgID;
    in >> m_ErrorInfo;
    in >> m_UserOperate;
    in >> m_OperateCmd;
    in >> m_RecvHost;
    in >> m_SendHost;
    in >> m_DataLength;
    in >> m_DataContent;
}

quint32 IMProtocol::getMsgID(void) const
{
    return m_MsgID;
}
void IMProtocol::setMsgID(const quint32 msgid)
{
    m_MsgID = msgid;
}

quint8 IMProtocol::getErrorInfo(void) const
{
    return m_ErrorInfo;
}
void IMProtocol::setErrorInfo(const quint8 errorinfo)
{
    m_ErrorInfo = errorinfo;
}

quint8 IMProtocol::getUserOperate(void) const
{
    return m_UserOperate;
}
void IMProtocol::setUserOperate(const quint8 useroperate)
{
    m_UserOperate = useroperate;
}

quint8 IMProtocol::getOperateCmd(void) const
{
    return m_OperateCmd;
}
void IMProtocol::setOperateCmd(const quint8 operatecmd)
{
    m_OperateCmd = operatecmd;
}

quint16 IMProtocol::getRecvHost(void) const
{
    return m_RecvHost;
}
void IMProtocol::setRecvHost(const quint16 recvhost)
{
    m_RecvHost = recvhost;
}

quint16 IMProtocol::getSendHost(void) const
{
    return m_SendHost;
}
void IMProtocol::setSendHost(const quint16 sendhost)
{
    m_SendHost = sendhost;
}

quint16 IMProtocol::getDataLength(void) const
{
    return m_DataLength;
}
void IMProtocol::setDataLength(const quint16 datalength)
{
    m_DataLength = datalength;
}

const QString &IMProtocol::getDataContent(void) const
{
    return m_DataContent;
}
void IMProtocol::setDataContent(const QString dataContent)
{
    m_DataContent = dataContent;
}
