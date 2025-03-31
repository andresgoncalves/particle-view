#include "AppWindow.h"

AppWindow::AppWindow(AppContext &appContext, QWidget *parent) : appContext{appContext}, QMainWindow{parent}
{
  appWidget = new AppWidget{appContext, this};
  setCentralWidget(appWidget);
  resize(800, 600);
}

AppWidget *AppWindow::getAppWidget()
{
  return appWidget;
}