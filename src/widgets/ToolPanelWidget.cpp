#include "ToolPanelWidget.h"

ToolPanelWidget::ToolPanelWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QFrame{parent}
{
  transformModesWidget = new TransformModesWidget{appContext, this};

  auto layout = new QVBoxLayout{this};
  layout->addWidget(transformModesWidget, 0, Qt::AlignTop);
  layout->setContentsMargins(8, 12, 8, 8);
}