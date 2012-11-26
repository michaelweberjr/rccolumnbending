#-------------------------------------------------
#
# Project created by QtCreator 2012-11-18T11:48:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rccolumnbending
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algorithm.cpp \
    rowdelete.cpp \
    rowadd.cpp \
    results.cpp \
    about.cpp \
    help.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    algorithm.h \
    steelbars.h \
    rowdelete.h \
    rowadd.h \
    results.h \
    about.h \
    help.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    rowdelete.ui \
    rowadd.ui \
    results.ui \
    about.ui \
    help.ui
