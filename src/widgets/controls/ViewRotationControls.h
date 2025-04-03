#ifndef VIEW_ROTATION_CONTROLS_H
#define VIEW_ROTATION_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class ViewRotationControls : public ControlSection
{
public:
  ViewRotationControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewRotationControls();

private:
  NumericControl *xRotationControl;
  NumericControl *yRotationControl;
  NumericControl *zRotationControl;

  AppContext &appContext;
};

#endif