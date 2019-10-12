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

TEMPLATE = aux

INSTALLER = "Ironmongery Installer"

DISTFILES += \
  resources/banner.jpg \
  resources/sunburst.icns \
  resources/sunburst.ico \
  resources/sunburst.png \
  packages/Ironmongery/meta/LICENSE \
  packages/Ironmongery/meta/package.xml \
  resources/watermark.jpg

RESOURCES += \
  installer.qrc

CONFIG(release, release|debug) {

    APP_DATA = $$PWD/packages/Ironmongery/data

    macx {
        APP_NAME = Ironmongery.app
        APP_PWD = $$OUT_PWD/../Ironmongery/$$APP_NAME
        cleandata.commands = test ! -e \"$$APP_DATA/$$APP_NAME\" || $$QMAKE_DEL_TREE \"$$APP_DATA/$$APP_NAME\"
        copydata.commands = $$QMAKE_COPY_DIR \"$$APP_PWD\" \"$$APP_DATA\"
        copydata.depends = cleandata
        export(cleandata.commands)
        export(copydata.depends)
        QMAKE_EXTRA_TARGETS += cleandata
    }

    win32 {
        APP_NAME = Ironmongery.exe
        APP_PWD = $$OUT_PWD/../Ironmongery/release
        copydata.commands = C:/Qt/Tools/QtInstallerFramework/3.1/bin/archivegen \"$$APP_DATA/application.7z\" \"$$APP_PWD/$$APP_NAME\" \"$$APP_PWD/*.dll\" \"$$APP_PWD/iconengines\" \"$$APP_PWD/imageformats\" \"$$APP_PWD/platforms\" \"$$APP_PWD/styles\" \"$$APP_PWD/translations\"
    }

    export(copydata.commands)

    QMAKE_EXTRA_TARGETS += first copydata

    INPUT = $$PWD/config/config.xml $$PWD/packages
    installer.depends = copydata
    installer.input = INPUT
    installer.output = \"$$INSTALLER\"
    macx: installer.commands = /opt/Qt/QtIFW-3.1.1/bin/binarycreator -f -c $$PWD/config/config.xml -p $$PWD/packages -r $$PWD/installer.qrc ${QMAKE_FILE_OUT}
    win32: installer.commands = C:/Qt/Tools/QtInstallerFramework/3.1/bin/binarycreator -f -c $$PWD/config/config.xml -p $$PWD/packages -r $$PWD/installer.qrc ${QMAKE_FILE_OUT}
    installer.CONFIG += target_predeps no_link combine

    QMAKE_EXTRA_COMPILERS += installer
}
