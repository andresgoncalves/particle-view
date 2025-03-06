#ifndef TOOL_PANEL_WIDGET_H
#define TOOL_PANEL_WIDGET_H

#include <QtWidgets/QFrame>

#include "toolpanel/TransformModesWidget.h"

class ToolPanelWidget : public QFrame
{
public:
  ToolPanelWidget(TransformController &transformController, QWidget *parent = nullptr);

private:
  TransformModesWidget *transformModesWidget;
};

#endif