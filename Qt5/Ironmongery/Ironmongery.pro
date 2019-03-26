# ------------------------------------------------------------------------------
#
# GDW RPG Vehicles, a vehicle database for Traveller and other GDW derived RPGs.
#
# Copyright (C) 2018-2019 Michael N. Henry <mike.henry@mikehenry.se>
#
# This file is part of GDW RPG Vehicles.
#
# GDW RPG Vehicles is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 2 of the License, or (at your option) any
# later version.
#
# GDW RPG Vehicles is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.
#
# See the GNU General Public License for more details. You should have received
# a copy of the GNU General Public License along with GDW RPG Vehicles. If not,
# see <http://www.gnu.org/licenses/>.
#
# ------------------------------------------------------------------------------

QT       += core widgets svg
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

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
    workspace.cc

HEADERS += \
    prefsdialog.hh \
    commands.hh \
    factory.hh \
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Ship/release/ -lShip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Ship/debug/ -lShip
else:unix: LIBS += -L$$OUT_PWD/../Ship/ -lShip

INCLUDEPATH += $$PWD/../Ship
DEPENDPATH += $$PWD/../Ship

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Unit/release/ -lUnit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Unit/debug/ -lUnit
else:unix: LIBS += -L$$OUT_PWD/../Unit/ -lUnit

INCLUDEPATH += $$PWD/../Unit
DEPENDPATH += $$PWD/../Unit

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
