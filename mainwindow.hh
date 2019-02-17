/*
**
**
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;

namespace Ui {
  class MainWindow;
  class VehicleForm;
  class WeaponForm;
}

namespace GDW
{
  namespace RPG
  {
    class MainWindow : public QMainWindow
    {
      Q_OBJECT

    public:
      explicit MainWindow(QWidget* parent = nullptr);
      ~MainWindow() override;

      void LoadFile(const QString& fileName);

    protected:
      void closeEvent(QCloseEvent* event) override;

    private slots:
      void NewFile();
      void Open();
      bool Save();
      bool SaveAs();
      void About();
      void DocumentWasModified();
      void Display(const QModelIndex&);
#ifndef QT_NO_SESSIONMANAGER
      void CommitData(QSessionManager&);
#endif

    private:
      void ReadSettings();
      void WriteSettings();
      bool MaybeSave();
      bool SaveFile(const QString& fileName);
      void SetCurrentFile(const QString& fileName);

      QPlainTextEdit* textEdit;
      QString curFile;

      Ui::MainWindow* mMainUi;
      Ui::VehicleForm* mVehicleUi;
      Ui::WeaponForm* mWeaponUi;
    };
  };
};
#endif // MAINWINDOW_HH
