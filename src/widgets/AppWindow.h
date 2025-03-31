#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QtWidgets/QMainWindow>

#include "AppWidget.h"
#include "../controllers/AppContext.h"

class AppWindow : public QMainWindow
{
public:
  AppWindow(AppContext &appContext, QWidget *parent = nullptr);

  AppWidget *getAppWidget();

private:
  AppWidget *appWidget;
  AppContext &appContext;
};

#endif