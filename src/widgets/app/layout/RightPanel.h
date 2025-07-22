#ifndef RIGHT_PANEL_H
#define RIGHT_PANEL_H

#include <QtWidgets/QTabWidget>

#include <controllers/AppContext.h>

/**
 * Right application panel
 */
class RightPanel : public QTabWidget
{
public:
  RightPanel(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif