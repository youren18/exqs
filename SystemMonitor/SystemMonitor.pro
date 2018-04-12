#-------------------------------------------------
#
# Project created by QtCreator 2018-03-18T17:09:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = SystemMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    tablemodel.cpp \
    tablewidget.cpp \
    prodate.cpp \
    info.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    tablemodel.h \
    tablewidget.h \
    prodate.h \
    info.h

FORMS    += mainwindow.ui


