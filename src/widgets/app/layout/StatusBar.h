#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <QtWidgets/QStatusBar>

#include <controllers/AppContext.h>

/**
 * Application status bar
 */
class StatusBar : public QStatusBar
{
public:
  StatusBar(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif