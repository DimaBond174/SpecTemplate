#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <i/itasks/itask1.h>
#include "const_common.h"
//#include <utils/hostosinfo.h>
#include <QNetworkInterface>

MainWindow::MainWindow(Presenter *in_presenter, QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow), presenter(in_presenter)
{
    ui->setupUi(this);
    onLayout();
    presenter->setCallback(this);
    //presenter->setContext(this, p_call);
}

MainWindow::~MainWindow()
{
  presenter->removeCallback();
}

void MainWindow::onLayout()
{
  //(void) new DocumentManager(this);

  //HistoryCompleter::setSettings(PluginManager::settings());
  foreach (const QHostAddress& address, QNetworkInterface::allAddresses() ) {
          qDebug() << address.toString();
      }
  setWindowTitle(Retail::IDE_DISPLAY_NAME);
  //if (HostOsInfo::isLinuxHost())
#if defined (Linux)
  QApplication::setWindowIcon(Icons::QTCREATORLOGO_BIG.icon());
#endif

  QCoreApplication::setApplicationName(QLatin1String(Constants::IDE_CASED_ID));
  QCoreApplication::setApplicationVersion(QLatin1String(Constants::IDE_VERSION_LONG));
  QCoreApplication::setOrganizationName(QLatin1String(Constants::IDE_SETTINGSVARIANT_STR));
  QGuiApplication::setApplicationDisplayName(QLatin1String(Constants::IDE_DISPLAY_NAME));
  QString baseName = QApplication::style()->objectName();
  // Sometimes we get the standard windows 95 style as a fallback
  if (HostOsInfo::isAnyUnixHost() && !HostOsInfo::isMacHost()
          && baseName == QLatin1String("windows")) {
      baseName = QLatin1String("fusion");
  }

  // if the user has specified as base style in the theme settings,
  // prefer that
  const QStringList available = QStyleFactory::keys();
  foreach (const QString &s, Utils::creatorTheme()->preferredStyles()) {
      if (available.contains(s, Qt::CaseInsensitive)) {
          baseName = s;
          break;
      }
  }

  QApplication::setStyle(new ManhattanStyle(baseName));
  m_generalSettings->setShowShortcutsInContextMenu(
      m_generalSettings->showShortcutsInContextMenu());

  setDockNestingEnabled(true);

  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

  m_modeManager = new ModeManager(this, m_modeStack);
  connect(m_modeStack, &FancyTabWidget::topAreaClicked, this, [](Qt::MouseButton, Qt::KeyboardModifiers modifiers) {
      if (modifiers & Qt::ShiftModifier) {
          QColor color = QColorDialog::getColor(StyleHelper::requestedBaseColor(), ICore::dialogParent());
          if (color.isValid())
              StyleHelper::setBaseColor(color);
      }
  });

  registerDefaultContainers();
  registerDefaultActions();

  m_leftNavigationWidget = new NavigationWidget(m_toggleLeftSideBarAction, Side::Left);
  m_rightNavigationWidget = new NavigationWidget(m_toggleRightSideBarAction, Side::Right);
  m_rightPaneWidget = new RightPaneWidget();

  m_messageManager = new MessageManager;
  m_editorManager = new EditorManager(this);
  m_externalToolManager = new ExternalToolManager();
  setCentralWidget(m_modeStack);

  m_progressManager->progressView()->setParent(this);

  connect(qApp, &QApplication::focusChanged, this, &MainWindow::updateFocusWidget);

  // Add small Toolbuttons for toggling the navigation widgets
  StatusBarManager::addStatusBarWidget(m_toggleLeftSideBarButton, StatusBarManager::First);
  int childsCount = statusBar()->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly).count();
  statusBar()->insertPermanentWidget(childsCount - 1, m_toggleRightSideBarButton); // before QSizeGrip

  statusBar()->setProperty("p_styled", true);

  auto dropSupport = new DropSupport(this, [](QDropEvent *event, DropSupport *) {
      return event->source() == nullptr; // only accept drops from the "outside" (e.g. file manager)
  });
  connect(dropSupport, &DropSupport::filesDropped,
          this, &MainWindow::openDroppedFiles);
} // onLayout


//void MainWindow::onLayout()
//{
//  QGridLayout *layout = new QGridLayout;

////  for (int i = 1; i < 10; ++ i) {
////      QLabel * const label = new QLabel(QString("CAM %1").arg(i, 2, 10, QLatin1Char('0')));
////      label->setFixedSize(200, 50);
////      layout->addWidget(label, (i-1) / 3, (i-1) % 3);
////      cams << label;
////  }
//  button1 = new QPushButton(tr("START"));
//  button1->setMinimumSize(200, 50);
//  layout->addWidget(button1, 1, 1);
//  QObject::connect(button1, &QPushButton::clicked,
//    [&]{
//      Data_Decor *p = Data_Decor::newObj();
//      p->type = 1;
//      ITask1 *task = ITask1::newObj("/home/dbond/workspace/video&photo/device-2018-05-22-083510.png");
//      p->source_data = task;
//      presenter->setTask_fromGUI(p);
//    }
//  );

//  button2 = new QPushButton(tr("STOP"));
//  button2->setMinimumSize(200, 50);
//  layout->addWidget(button2, 2, 1);
//  QObject::connect(button2, &QPushButton::clicked,
//     [&]{
//    //testGUI();
//     }
//  );

//  imgView1 = new CustomView();
//  imgView1->setMinimumSize(200, 200);
//  imgView1->setCursor(Qt::PointingHandCursor);
//  //imgView1->setSizePolicy();
//  layout->addWidget(imgView1, 2, 2);

//  QWidget * central = new QWidget();
//  setCentralWidget(central);
//  centralWidget()->setLayout(layout);

//  setWindowTitle("Camera Window");
// // setFixedSize(1000, 800);
//  setBaseSize(1000, 800);
//} // onLayout

void MainWindow::runAtGUIthread()
{
   QMetaObject::invokeMethod(
          this,
         [&]() -> void {
           //std::invoke(callable, std::forward<Args>(args)...);
         },
         Qt::BlockingQueuedConnection
  );
   return;
}

void MainWindow::onCallResult(Data_Decor *result)
{
  // WARNING: must run at GUI thread
  switch (result->type)
  {
  case 1:
    QMetaObject::invokeMethod(
           this,
          [&]() -> void {
            //std::invoke(callable, std::forward<Args>(args)...);
            showImg(result);
          },
          Qt::BlockingQueuedConnection
   );
    break;
  default:
    break;
  } //switch
  //TODO free result void ptr's.. or it's will killed:
  // see Qt::BlockingQueuedConnection - must waited
  Data_Decor::freeObj(result); //https://doc.qt.io/archives/qtjambi-4.5.2_01/com/trolltech/qt/core/Qt.ConnectionType.html
  return;
} //onCallResult

void MainWindow::testGUI()
{
  for (int i = 0; i < 10000000; ++i)
  {
    button1->setText(tr(std::to_string(i).c_str()));
  }
  return;
} //testGUI

 void MainWindow::showImg(Data_Decor *result)
 {
   if (Data_Decor::isValid(result))
   {
     if (result->res_data)
     {
       ITask1_Result * res = static_cast<ITask1_Result *>(result->res_data);
       imgView1->showImg(res);
       ITask1_Result::freeObj(res);
       result->res_data = nullptr;
     }
   }
 } // showImg
