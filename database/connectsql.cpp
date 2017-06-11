#include "connectsql.h"
#include <QDebug>
#include <QSqlError>

DataBase::DataBase()
{//建立连接
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");  //建立一个连接
    db.setDatabaseName("../database/IM.db");    //set数据库的名字

    if(!db.open())
    {//建立真正的物理连接没成功时
        qCritical("Conn't open %s(%s) sql....",
                  db.lastError().text().toLocal8Bit().data(),   //QSqlError.QString.QByteArray.char*
                  qt_error_string().toLocal8Bit().data());  //
    }
}

DataBase::~DataBase()
{//断开连接
    QSqlDatabase::database().close();
}
