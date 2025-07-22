#include "CenterPanel.h"

#include <QtWidgets/QStackedLayout>

#include <widgets/app/scene/SceneWidget.h>

CenterPanel::CenterPanel(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  auto sceneWidget = new SceneWidget{appContext, this};
  auto layout = new QStackedLayout{this};
  layout->addWidget(sceneWidget);
}