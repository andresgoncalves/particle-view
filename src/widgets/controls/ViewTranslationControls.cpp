#include "ViewTranslationControls.h"

#include <QtWidgets/QHBoxLayout>

ViewTranslationControls::ViewTranslationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Traslación", parent}
{

  xTranslationControl = new NumericControl{"x:", this};
  xTranslationControl->onChange<float>([&](float value)
                                       { appContext.viewController.setTranslationX(value); });
  yTranslationControl = new NumericControl{"y:", this};
  yTranslationControl->onChange<float>([&](float value)
                                       { appContext.viewController.setTranslationY(value); });
  zTranslationControl = new NumericControl{"z:", this};
  zTranslationControl->onChange<float>([&](float value)
                                       { appContext.viewController.setTranslationZ(value); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(xTranslationControl);
  layout->addWidget(yTranslationControl);
  layout->addWidget(zTranslationControl);
  layout->setContentsMargins({});

  auto translationCallback = [&](QVector3D value)
  {
    xTranslationControl->setValue(value.x());
    yTranslationControl->setValue(value.y());
    zTranslationControl->setValue(value.z());
  };

  translationCallback(appContext.viewController.translationObservable.get());

  appContext.viewController.translationObservable.subscribe(this, translationCallback);
}

ViewTranslationControls::~ViewTranslationControls()
{
  appContext.viewController.translationObservable.unsubscribe(this);
}