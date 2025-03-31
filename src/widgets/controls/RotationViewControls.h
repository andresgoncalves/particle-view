#ifndef ROTATION_VIEW_CONTROLS_H
#define ROTATION_VIEW_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class RotationViewControls : public ControlSection
{
public:
  RotationViewControls(AppContext &appContext, QWidget *parent = nullptr);
  ~RotationViewControls();

private:
  NumericControl *xRotationControl;
  NumericControl *yRotationControl;
  NumericControl *zRotationControl;

  AppContext &appContext;
};

#endif