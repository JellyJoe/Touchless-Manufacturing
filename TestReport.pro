#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T19:23:13
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testreport
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testreport.cpp \
    Report.cpp \
    tinyxml2.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx: LIBS += -L$$PWD/../Touchless-Manufacturing/ -ltinyxml2

INCLUDEPATH += $$PWD/../Touchless-Manufacturing
DEPENDPATH += $$PWD/../Touchless-Manufacturing

unix:!macx: PRE_TARGETDEPS += $$PWD/../Touchless-Manufacturing/libtinyxml2.a

HEADERS += \
    Report.h \
    tinyxml2.h
