/*
**
**
*/

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLibraryInfo>
#include <QTranslator>

#include "mainwindow.hh"

int main(int argc, char* argv[])
{
  Q_INIT_RESOURCE(gdw_rpg_vehicles);

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Mike Henry");
  QCoreApplication::setApplicationName("GDW RPG Vehicles");
  QCoreApplication::setApplicationVersion("0");
  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "The file to open.");
  parser.process(app);

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  QTranslator myappTranslator;
  myappTranslator.load("grv_" + QLocale::system().name());
  app.installTranslator(&myappTranslator);

  GDW::RPG::MainWindow mainWin;
  if (!parser.positionalArguments().isEmpty())
    mainWin.LoadFile(parser.positionalArguments().first());
  mainWin.show();
  return app.exec();
}
