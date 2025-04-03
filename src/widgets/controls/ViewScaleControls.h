#ifndef VIEW_SCALE_CONTROLS_H
#define VIEW_SCALE_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class ViewScaleControls : public ControlSection
{
public:
  ViewScaleControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewScaleControls();

private:
  NumericControl *scaleControl;

  AppContext &appContext;
};

#endif