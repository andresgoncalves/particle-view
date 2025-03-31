#ifndef SCENE_CONTROL_PANEL_H
#define SCENE_CONTROL_PANEL_H

#include <QtWidgets/QWidget>

#include "../../controllers/AppContext.h"

class SceneControlPanel : public QWidget
{
public:
  SceneControlPanel(AppContext &appContext, QWidget *parent);

private:
  AppContext &appContext;
};

#endif