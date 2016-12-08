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

unix:!macx: LIBS += -L$$PWD/./ -ltinyxml2

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/./libtinyxml2.a

HEADERS += \
    Report.h \
    tinyxml2.h
