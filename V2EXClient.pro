#-------------------------------------------------
#
# Project created by QtCreator 2016-12-24T09:31:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = V2EXClient
TEMPLATE = app


SOURCES += main.cpp\
        v2exwindow.cpp \
    v2ex.cpp \
    networkimage.cpp \
    nodeinfo.cpp \
    memberinfo.cpp \
    topicinfo.cpp

HEADERS  += v2exwindow.h \
    v2ex.h \
    networkimage.h \
    nodeinfo.h \
    memberinfo.h \
    topicinfo.h

FORMS    += v2exwindow.ui
