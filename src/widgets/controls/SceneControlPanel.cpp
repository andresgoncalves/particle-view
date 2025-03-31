#include "SceneControlPanel.h"

#include <QtWidgets/QVBoxLayout>

#include "ToolControls.h"

SceneControlPanel::SceneControlPanel(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  auto toolControls = new ToolControls{appContext, this};

  auto layout = new QVBoxLayout{this};
  layout->addWidget(toolControls, 0, Qt::AlignTop);
  layout->setContentsMargins(8, 12, 8, 8);
}