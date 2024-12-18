#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "AppWidget.h"
#include "AppWindow.h"

AppWindow::AppWindow(QWidget *parent) : QMainWindow{parent}
{
  auto appWidget = new AppWidget{this};
  setCentralWidget(appWidget);
}