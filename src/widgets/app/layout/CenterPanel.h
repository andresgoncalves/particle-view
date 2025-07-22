#ifndef CENTER_PANEL_H
#define CENTER_PANEL_H

#include <QtWidgets/QWidget>

#include <controllers/AppContext.h>

/**
 * Application center panel
 */
class CenterPanel : public QWidget
{
public:
  /** Creates the center panel, composed by a SceneWidget */
  CenterPanel(AppContext &appContext, QWidget *parent = nullptr);

private:
  /** Application context */
  AppContext &appContext;
};

#endif