#ifndef VIEW_CONTROLS_H
#define VIEW_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class ViewControls : public ControlSection
{
public:
  ViewControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewControls();

private:
  NumericControl *xTranslationControl;
  NumericControl *yTranslationControl;
  NumericControl *zTranslationControl;

  AppContext &appContext;
};

#endif