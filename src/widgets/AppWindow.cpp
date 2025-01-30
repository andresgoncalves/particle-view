#include "AppWindow.h"

AppWindow::AppWindow(QWidget *parent) : QMainWindow{parent}
{
  appWidget = new AppWidget{this};
  setCentralWidget(appWidget);
  resize(800, 600);
}

AppWidget *AppWindow::getAppWidget()
{
  return appWidget;
}