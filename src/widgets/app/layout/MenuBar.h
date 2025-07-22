#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <QtWidgets/QMenuBar>

#include <controllers/AppContext.h>

/**
 * Application menu bar
 */
class MenuBar : public QMenuBar
{
public:
  MenuBar(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif