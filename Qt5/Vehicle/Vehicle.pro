#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T16:55:12
#
#-------------------------------------------------

QT       += core widgets svg
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = Vehicle
TEMPLATE = lib

DEFINES += VEHICLE_LIBRARY

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
    vehicle.cc \
    vehicleform.cc \
    vehicleitem.cc \
    vehiclemodel.cc

HEADERS += \
    vehicle_global.hh \
    vehicle.hh \
    vehicleform.hh \
    vehicleitem.hh \
    vehiclemodel.hh

FORMS += \
    vehicleform.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Object/release/ -lObject
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Object/debug/ -lObject
else:unix: LIBS += -L$$OUT_PWD/../Object/ -lObject

INCLUDEPATH += $$PWD/../Object
DEPENDPATH += $$PWD/../Object

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Weapon/release/ -lWeapon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Weapon/debug/ -lWeapon
else:unix: LIBS += -L$$OUT_PWD/../Weapon/ -lWeapon

INCLUDEPATH += $$PWD/../Weapon
DEPENDPATH += $$PWD/../Weapon

RESOURCES += \
    vehicle.qrc
