#include "munitionform.hh"
#include "ui_munitionform.h"

MunitionForm::MunitionForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MunitionForm)
{
  ui->setupUi(this);
}

MunitionForm::~MunitionForm()
{
  delete ui;
}
