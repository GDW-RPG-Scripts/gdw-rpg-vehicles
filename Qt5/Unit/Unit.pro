#-------------------------------------------------
#
# Project created by QtCreator 2019-03-22T23:37:58
#
#-------------------------------------------------

QT       += widgets svg

QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = Unit
TEMPLATE = lib

DEFINES += UNIT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    unit.cc \
    unititem.cc \
    unitmodel.cc \
    unitform.cc

HEADERS += \
    unit.hh \
    unit_global.hh \
    unititem.hh \
    unitmodel.hh \
    unitform.hh

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Object/release/ -lObject
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Object/debug/ -lObject
else:unix: LIBS += -L$$OUT_PWD/../Object/ -lObject

INCLUDEPATH += $$PWD/../Object
DEPENDPATH += $$PWD/../Object

FORMS += \
    unitform.ui
