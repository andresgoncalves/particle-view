#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include <QtWidgets/QToolBar>

#include <controllers/AppContext.h>

/**
 * Application tool bar
 */
class ToolBar : public QToolBar
{
public:
  ToolBar(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif