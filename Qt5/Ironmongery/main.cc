/**
 * GDW RPG Vehicles, a vehicle database for Traveller and other GDW derived RPGs.
 *
 * Copyright (C) 2018-2019 Michael N. Henry
 *
 * This file is part of GDW RPG Vehicles.
 *
 * GDW RPG Vehicles is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * GDW RPG Vehicles is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with GDW RPG Vehicles. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QLibraryInfo>
#include <QTranslator>

#include "mainwindow.hh"

int main(int argc, char* argv[])
{
  Q_INIT_RESOURCE(Ironmongery);

  QApplication application(argc, argv);

  QCoreApplication::setOrganizationName("");
  QCoreApplication::setApplicationName("Ironmongery");
  QCoreApplication::setApplicationVersion("0");

  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "The file to open.");
  parser.process(application);

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  application.installTranslator(&qtTranslator);

  QTranslator appTranslator;
  appTranslator.load(QLocale(), QLatin1String("Ironmongery"),
                       QLatin1String("_")); //, QLatin1String(":/translations"));
  application.installTranslator(&appTranslator);

  GDW::RPG::MainWindow mainWindow;
  if (!parser.positionalArguments().isEmpty())
    mainWindow.LoadFile(parser.positionalArguments().first());
  mainWindow.show();

  return application.exec();
}
