#include "ToolPanelWidget.h"

ToolPanelWidget::ToolPanelWidget(TransformController &transformController, QWidget *parent) : QFrame{parent}
{
  transformModesWidget = new TransformModesWidget{transformController, this};

  auto layout = new QVBoxLayout{this};
  layout->addWidget(transformModesWidget, 0, Qt::AlignTop);
  layout->setContentsMargins(8, 12, 8, 8);
}