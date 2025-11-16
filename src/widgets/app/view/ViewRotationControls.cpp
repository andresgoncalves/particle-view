#include "ViewRotationControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/VectorControl.h>

ViewRotationControls::ViewRotationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Rotación", parent}
{
  // Rotation control
  auto rotationControl = new VectorControl{{"x:", "y:", "z:"}, this};
  rotationControl->onChange([&appContext](QVector3D value)
                            { appContext.viewController.setRotation(value); });
  // Set dimensionality
  auto dimensionalityCallback = [=](ViewController::Dimensionality dimensionality)
  {
    if (dimensionality == ViewController::Dimensionality::Dimension2D)
    {
      rotationControl->setVisibleComponents({false, false, true});
      rotationControl->getControls()[2]->getLabel()->hide();
    }
    else
    {
      rotationControl->setVisibleComponents({true, true, true});
      rotationControl->getControls()[2]->getLabel()->show();
    }
  };
  appContext.viewController.dimensionalityObservable.subscribe(this, dimensionalityCallback, true);

  // Reset button
  auto resetButton = new QPushButton{"Reiniciar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setRotation({}); });

  auto layout = new QVBoxLayout{content};
  layout->addWidget(rotationControl);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add rotation listener
  auto rotationCallback = [=](QVector3D value)
  {
    rotationControl->setValue(value);
  };
  appContext.viewController.rotationObservable.subscribe(this, rotationCallback, true);
}

ViewRotationControls::~ViewRotationControls()
{
  appContext.viewController.rotationObservable.unsubscribe(this);
}