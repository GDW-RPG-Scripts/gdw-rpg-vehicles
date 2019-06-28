TEMPLATE = aux

INSTALLER = "Ironmongery Installer"

INPUT = $$PWD/config/config.xml $$PWD/packages
example.input = INPUT
example.output = $$INSTALLER
example.commands = /Applications/Qt/Tools/QtInstallerFramework/3.1/bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
example.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += example

OTHER_FILES = README

FORMS += \
  packages/Ironmongery/meta/page.ui

DISTFILES += \
  packages/Ironmongery.Weapon/data/Weapon.7z \
  resources/banner.jpg \
  resources/sunburst.icns \
  resources/sunburst.ico \
  resources/sunburst.png \
  packages/Ironmongery.Object/meta/package.xml \
  packages/Ironmongery.Ship/meta/package.xml \
  packages/Ironmongery.Unit/meta/package.xml \
  packages/Ironmongery.Vehicle/meta/package.xml \
  packages/Ironmongery.Weapon/meta/package.xml \
  packages/Ironmongery/data/installcontent.txt \
  packages/Ironmongery/meta/installscript.qs \
  packages/Ironmongery/meta/license.txt \
  packages/Ironmongery/meta/package.xml \
  resources/watermark.jpg
