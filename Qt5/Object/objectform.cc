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

#include "objectform.hh"

#include <QDebug>
#include <QHBoxLayout>
#include <QSvgRenderer>
#include <QSvgWidget>
#include <QtWidgets>

using namespace GDW::RPG;

ObjectForm::ObjectForm(QWidget* parent, QUndoStack* undoStack) :
  QWidget(parent), mReadOnly(true), mUndoStack(undoStack)
{}

ObjectForm::~ObjectForm()
{}

Object*
ObjectForm::Read(Mode, Object*)
{
  return nullptr;
}

Object*
ObjectForm::Write()
{
  return nullptr;
}

bool
ObjectForm::IsReadOnly() const
{
  return mReadOnly;
}

void
ObjectForm::SetReadOnly(bool value)
{
  mReadOnly = value;
}

QString
ObjectForm::Title() const
{
  return "";
}

Object*
ObjectForm::GetObject()
{
  return nullptr;
}

const Object*
ObjectForm::GetObject() const
{
  return nullptr;
}

QUndoStack*
ObjectForm::UndoStack()
{
  return mUndoStack;
}

void
ObjectForm::AddSvgFrame(const QVariant& data, QWidget* parent)
{
  if(!data.isValid())
    return;

  QSvgWidget* svg = nullptr;

  if(!data.toByteArray().isEmpty()) {
    QByteArray base64 = data.toByteArray();
    QByteArray fragment = qUncompress(QByteArray::fromBase64(base64));

    svg = new QSvgWidget;
    svg->load(fragment);
  }

  QHBoxLayout* hbox = new QHBoxLayout;
  hbox->setContentsMargins(2,2,2,2);
  hbox->addWidget(svg);

  QLayout* layout = parent->layout();
  if(layout)
    delete layout;
  parent->setLayout(hbox);
  parent->update();
}

QByteArray
ObjectForm::GetSvgFragment(const QString& message)
{
  QString fileName =
      QFileDialog::getOpenFileName(this, message, ".",
                                   tr("SVG files (*.svg)"));
  if (fileName.isEmpty())
    return "";

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return "";

  QByteArray result;
  QXmlStreamReader xml(&file);

  int level = 0;
  while (!xml.atEnd()) {
    QXmlStreamReader::TokenType type = xml.readNext();
    switch(type) {
      case QXmlStreamReader::NoToken:
        qDebug() << "<!-- No Token -->";
        break;

      case QXmlStreamReader::Invalid:
        qDebug() << "<!-- Invalid -->";
        break;

      case QXmlStreamReader::StartDocument:
        qDebug() << "<!-- Start Dockument -->";
        break;

      case QXmlStreamReader::EndDocument:
        qDebug() << "<!-- End Dockument -->";
        break;

      case QXmlStreamReader::StartElement:
      {
        QString indent;
        for (int i = 0; i < level; i++) {
          indent += "  ";
        }
        QString nsDecls;
        for(QXmlStreamNamespaceDeclaration nd: xml.namespaceDeclarations()){
          nsDecls += (nd.prefix().isEmpty() ? " xmlns" : " xmlns:")
                     + nd.prefix() + "=\"" + nd.namespaceUri() + "\"";
        }
        QString attributes;
        for(QXmlStreamAttribute a: xml.attributes()) {
          attributes += " " + a.name() + "=\"" + a.value() + "\"";
        }
        result += "<" + xml.name() + nsDecls + attributes + ">";
        qDebug().noquote().nospace()
            << indent
            << "<" << xml.name()
            << nsDecls
            << attributes
            << ">";
        level += 1;
        break;
      }

      case QXmlStreamReader::EndElement:
      {
        level -= 1;
        QString indent;
        for (int i = 0; i < level; i++) {
          indent += "  ";
        }
        result += "</" + xml.name() + ">";
        qDebug().noquote().nospace()
            << indent
            << "</" << xml.name() << ">";
        break;
      }

      case QXmlStreamReader::Characters:
      {
        QString indent;
        for (int i = 0; i < level; i++) {
          indent += "  ";
        }
        if(!xml.isWhitespace()) {
          result += xml.text().toString();
          qDebug().noquote().nospace()
              << indent
              << "  " << xml.text();
        }
        break;
      }

      case QXmlStreamReader::Comment:
        qDebug() << "<!-- Comment -->";
        break;

      case QXmlStreamReader::DTD:
        qDebug() << "<!-- DTD -->";
        break;

      case QXmlStreamReader::EntityReference:
        qDebug() << "<!-- EntityReference -->";
        break;

      case QXmlStreamReader::ProcessingInstruction:
        qDebug() << "<!-- ProcessingInstruction -->";
        break;
    }
  }

  if(xml.hasError()) {
    qDebug() << xml.errorString();
    return "";
  }

  return qCompress(result, 9).toBase64();
}
