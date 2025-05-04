#include "ViewScaleControls.h"

#include <QtWidgets/QHBoxLayout>

ViewScaleControls::ViewScaleControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Escala", parent}
{

  scaleControl = new NumericControl{this};
  scaleControl->onChange<float>([&](float value)
                                { appContext.viewController.setScale(value); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(scaleControl);
  layout->setContentsMargins({});

  auto scaleCallback = [&](float value)
  {
    scaleControl->setValue(value);
  };

  scaleCallback(appContext.viewController.scaleObservable.get());

  appContext.viewController.scaleObservable.subscribe(this, scaleCallback);
}

ViewScaleControls::~ViewScaleControls()
{
  appContext.viewController.scaleObservable.unsubscribe(this);
}