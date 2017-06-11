#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T09:20:47
#
#-------------------------------------------------

QT       += core gui  sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IMserver_1
TEMPLATE = app

INCLUDEPATH += $$PWD/include
include(widgets/widgets.pri)
include(common/common.pri)
include(database/database.pri)
include(logfile/logfile.pri)
include(network/network.pri)
include(protocol/protocol.pri)

SOURCES += main.cpp \
    logiclayer.cpp

HEADERS  += \
    logiclayer.h

FORMS    +=
