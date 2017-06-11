#include <QApplication>
#include "logiclayer.h"
#include "connectsql.h"
//#include "sqlanalysis.h"
//#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase db;    //连接sql
    LogicLayer logic;   //Model

//    SQLAnalysis::getTotalCrowdMember();
//    qDebug() << SQLAnalysis::m_crowdMemberTotal;

    return a.exec();
}
