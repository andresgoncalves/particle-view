#include "SceneControlPanel.h"

#include <QtWidgets/QVBoxLayout>

#include "ToolControls.h"
#include "ViewControls.h"

SceneControlPanel::SceneControlPanel(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  auto toolControls = new ToolControls{appContext, this};
  auto viewControls = new ViewControls{appContext, this};

  auto layout = new QVBoxLayout{this};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(toolControls);
  layout->addWidget(viewControls);
  layout->setContentsMargins(0, 8, 0, 8);
}