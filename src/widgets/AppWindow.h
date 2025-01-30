#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QtWidgets/QMainWindow>

#include "AppWidget.h"

class AppWindow : public QMainWindow
{
public:
  AppWindow(QWidget *parent = nullptr);

  AppWidget *getAppWidget();

private:
  AppWidget *appWidget;
};

#endif