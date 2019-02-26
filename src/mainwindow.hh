/*
**
**
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QUndoStack>

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
    class TreeModel;

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
        void New();
        void Open();
        bool Save();
        bool SaveAs();
        void Redo();
        void Undo();

        void About();
        void DocumentWasModified();

        void AddItem();
        void EditItem();
        void PrintItem();
        void SelectItem(const QModelIndex&);
        void SaveItem();

#ifndef QT_NO_SESSIONMANAGER
        void CommitData(QSessionManager&);
#endif

      private:
        void ReadSettings();
        void WriteSettings();
        bool isModified();
        bool MaybeSave();
        bool SaveFile(const QString& fileName);
        void SetCurrentFile(const QString& fileName);

        TreeModel* mModel;

        QString mCurrentFile;        
        QUndoStack mUndoStack;
        Ui::MainWindow* mUi;

        // QPlainTextEdit* textEdit;
    };
  };
};
#endif // MAINWINDOW_HH
