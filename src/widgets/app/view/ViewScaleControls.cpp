#include "ViewScaleControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/NumericControl.h>

ViewScaleControls::ViewScaleControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Escala", parent}
{
  // Scale control
  auto scaleControl = new NumericControl{this};
  scaleControl->onChange<float>([&appContext](float value)
                                { appContext.viewController.setScale(value); });

  // Reset button
  auto resetButton = new QPushButton{"Reiniciar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setScale(1.0f); });

  // Build layout
  auto controlLayout = new QHBoxLayout{};
  controlLayout->addWidget(scaleControl);
  controlLayout->setContentsMargins({});

  auto layout = new QVBoxLayout{content};
  layout->addLayout(controlLayout);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add scale listener
  auto scaleCallback = [=](float value)
  {
    scaleControl->setValue(value);
  };
  appContext.viewController.scaleObservable.subscribe(this, scaleCallback, true);
}

ViewScaleControls::~ViewScaleControls()
{
  appContext.viewController.scaleObservable.unsubscribe(this);
}