#ifndef TRANSLATION_VIEW_CONTROLS_H
#define TRANSLATION_VIEW_CONTROLS_H

#include <QtWidgets/QWidget>

#include "ControlSection.h"
#include "NumericControl.h"
#include "../../controllers/AppContext.h"

class TranslationViewControls : public ControlSection
{
public:
  TranslationViewControls(AppContext &appContext, QWidget *parent = nullptr);
  ~TranslationViewControls();

private:
  NumericControl *xTranslationControl;
  NumericControl *yTranslationControl;
  NumericControl *zTranslationControl;

  AppContext &appContext;
};

#endif