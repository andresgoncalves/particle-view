#ifndef SCALE_VIEW_CONTROLS_H
#define SCALE_VIEW_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class ScaleViewControls : public ControlSection
{
public:
  ScaleViewControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ScaleViewControls();

private:
  NumericControl *scaleControl;

  AppContext &appContext;
};

#endif