#ifndef SCENE_CONTROL_PANEL_H
#define SCENE_CONTROL_PANEL_H

#include <QtWidgets/QScrollArea>

#include "../../controllers/AppContext.h"

class SceneControlPanel : public QScrollArea
{
public:
  SceneControlPanel(AppContext &appContext, QWidget *parent);

private:
  AppContext &appContext;
};

#endif