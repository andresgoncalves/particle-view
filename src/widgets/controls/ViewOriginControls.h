#ifndef VIEW_ORIGIN_CONTROLS_H
#define VIEW_ORIGIN_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class ViewOriginControls : public ControlSection
{
public:
  ViewOriginControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewOriginControls();

private:
  NumericControl *xOriginControl;
  NumericControl *yOriginControl;
  NumericControl *zOriginControl;

  AppContext &appContext;
};

#endif