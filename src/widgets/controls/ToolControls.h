#ifndef TOOL_CONTROLS_H
#define TOOL_CONTROLS_H

#include <functional>

#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "../../controllers/AppContext.h"

class ToolControls : public ControlSection
{
public:
  ToolControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ToolControls();

private:
  QLabel *label;
  QPushButton *rotateXYButton;
  QPushButton *rotateZButton;
  QPushButton *translateXYButton;
  QPushButton *translateZButton;
  QPushButton *scaleButton;

  AppContext &appContext;

  std::function<void(TransformController::TransformType)> transformTypeCallback;
};

#endif