#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QtWidgets/QMainWindow>

#include "../controllers/RenderController.h"

class AppWindow : public QMainWindow
{
public:
  AppWindow(QWidget *parent = nullptr);
};

#endif