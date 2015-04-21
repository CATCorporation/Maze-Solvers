#-------------------------------------------------
#
# Project created by QtCreator 2015-04-21T11:42:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeServeur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serv.cpp

HEADERS  += mainwindow.h \
    serv.h

FORMS    += mainwindow.ui
