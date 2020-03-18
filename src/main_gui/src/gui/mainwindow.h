#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QScopedPointer>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <src/presenter.h>
#include <i/idatacallback.h>
#include "widgets/customview.h"
// TODO попробовать Material Design
//https://github.com/qt/qtquickcontrols2
//#include <QtQuickControls2>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow, public IDataCallback {
    Q_OBJECT

public:
    MainWindow(Presenter *in_presenter, QWidget *parent = nullptr);
    virtual ~MainWindow();

    void onCallResult(Data_Decor *result) override;

private:
  QScopedPointer<Ui::MainWindow> ui;
  QVector<QLabel*> cams;
  QPushButton  *button1;
  QPushButton  *button2;
  CustomView  *imgView1;

  Presenter *const presenter;

  // Prepare Layout:
  void onLayout();

  // Execute at GUI thread:
  void runAtGUIthread();
  void testGUI();
  void showImg(Data_Decor *result);

};

#endif
