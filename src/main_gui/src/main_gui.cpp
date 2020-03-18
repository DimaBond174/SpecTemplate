#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    Presenter presenter;
    MainWindow mainWindow(&presenter);
    mainWindow.show();
    return app.exec();
}
