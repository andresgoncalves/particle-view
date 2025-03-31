#ifndef TOOL_PANEL_WIDGET_H
#define TOOL_PANEL_WIDGET_H

#include <QtWidgets/QFrame>

#include "toolpanel/TransformModesWidget.h"

#include "../controllers/AppContext.h"

class ToolPanelWidget : public QFrame
{
public:
  ToolPanelWidget(AppContext &appContext, QWidget *parent = nullptr);

private:
  TransformModesWidget *transformModesWidget;

  AppContext &appContext;
};

#endif