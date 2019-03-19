#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T11:16:08
#
#-------------------------------------------------

QT       += core gui printsupport svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ironmongery
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += lrelease embed_translations

SOURCES += \
    main.cc \
    prefsdialog.cc \
    commands.cc \
    factory.cc \
    vehiclemodel.cc \
    workspace.cc

HEADERS += \
    prefsdialog.hh \
    commands.hh \
    factory.hh \
    vehiclemodel.hh \
    workspace.hh

# TRANSLATIONS += \
#    $$PWD/translations/gdw_rpg_vehicles_sv.ts

TRANSLATIONS = \
    translations/Ironmongery_sv.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    workspace.ui

RESOURCES += \
    Ironmongery.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Object/release/ -lObject
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Object/debug/ -lObject
else:unix: LIBS += -L$$OUT_PWD/../Object/ -lObject

INCLUDEPATH += $$PWD/../Object
DEPENDPATH += $$PWD/../Object

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Vehicle/release/ -lVehicle
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Vehicle/debug/ -lVehicle
else:unix: LIBS += -L$$OUT_PWD/../Vehicle/ -lVehicle

INCLUDEPATH += $$PWD/../Vehicle
DEPENDPATH += $$PWD/../Vehicle

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Weapon/release/ -lWeapon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Weapon/debug/ -lWeapon
else:unix: LIBS += -L$$OUT_PWD/../Weapon/ -lWeapon

INCLUDEPATH += $$PWD/../Weapon
DEPENDPATH += $$PWD/../Weapon
