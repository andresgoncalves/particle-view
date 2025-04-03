#ifndef VIEW_TRANSLATION_CONTROLS_H
#define VIEW_TRANSLATION_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class ViewTranslationControls : public ControlSection
{
public:
  ViewTranslationControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewTranslationControls();

private:
  NumericControl *xTranslationControl;
  NumericControl *yTranslationControl;
  NumericControl *zTranslationControl;

  AppContext &appContext;
};

#endif