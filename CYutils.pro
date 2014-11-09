#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T16:35:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CYutils
TEMPLATE = app


SOURCES += main.cpp\
        cyutil.cpp \
    partprobe.c

HEADERS  += cyutil.h \
    partprobe.h

FORMS    += cyutil.ui

LIBS += -lparted
