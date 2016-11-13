QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    MyClass.cpp \
    Serial.cpp \
    Report.cpp \
    tinyxml2.cpp \
    Arm.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    MyClass.h \
    Serial.h \
    Report.h \
    tinyxml2.h \
    Arm.h

unix:!macx: LIBS += -L$$PWD/./ -ltinyxml2

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/./libtinyxml2.a
