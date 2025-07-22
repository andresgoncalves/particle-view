#ifndef LEFT_PANEL_H
#define LEFT_PANEL_H

#include <QtWidgets/QTabWidget>

#include <controllers/AppContext.h>

/**
 * Application left panel
 */
class LeftPanel : public QTabWidget
{
public:
  /**
   * Creates the center panel, composed by:
   * - ViewTab
   * - AnimationTab
   * - DisplayTab
   */
  LeftPanel(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif