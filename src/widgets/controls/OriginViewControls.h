#ifndef ORIGIN_VIEW_CONTROLS_H
#define ORIGIN_VIEW_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class OriginViewControls : public ControlSection
{
public:
  OriginViewControls(AppContext &appContext, QWidget *parent = nullptr);
  ~OriginViewControls();

private:
  NumericControl *xOriginControl;
  NumericControl *yOriginControl;
  NumericControl *zOriginControl;

  AppContext &appContext;
};

#endif