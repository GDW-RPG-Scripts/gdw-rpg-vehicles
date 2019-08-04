#ifndef MUNITIONFORM_HH
#define MUNITIONFORM_HH

#include <QWidget>

namespace Ui {
  class MunitionForm;
}

class MunitionForm : public QWidget
{
    Q_OBJECT

  public:
    explicit MunitionForm(QWidget *parent = nullptr);
    ~MunitionForm();

  private:
    Ui::MunitionForm *ui;
};

#endif // MUNITIONFORM_HH
