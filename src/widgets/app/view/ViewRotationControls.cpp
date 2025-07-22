#include "ViewRotationControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/NumericControl.h>

ViewRotationControls::ViewRotationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Rotación", parent}
{
  // Rotation X control
  auto xRotationControl = new NumericControl{"x:", this};
  xRotationControl->onChange<float>([&appContext](float value)
                                    { appContext.viewController.setRotationX(value); });

  // Rotation Y control
  auto yRotationControl = new NumericControl{"y:", this};
  yRotationControl->onChange<float>([&appContext](float value)
                                    { appContext.viewController.setRotationY(value); });

  // Rotation Z control
  auto zRotationControl = new NumericControl{"z:", this};
  zRotationControl->onChange<float>([&appContext](float value)
                                    { appContext.viewController.setRotationZ(value); });

  // Reset button
  auto resetButton = new QPushButton{"Reiniciar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setRotation({}); });

  // Build layout
  auto controlLayout = new QHBoxLayout{};
  controlLayout->addWidget(xRotationControl);
  controlLayout->addWidget(yRotationControl);
  controlLayout->addWidget(zRotationControl);
  controlLayout->setContentsMargins({});

  auto layout = new QVBoxLayout{content};
  layout->addLayout(controlLayout);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add rotation listener
  auto rotationCallback = [=](QVector3D value)
  {
    xRotationControl->setValue(value.x());
    yRotationControl->setValue(value.y());
    zRotationControl->setValue(value.z());
  };
  appContext.viewController.rotationObservable.subscribe(this, rotationCallback, true);
}

ViewRotationControls::~ViewRotationControls()
{
  appContext.viewController.rotationObservable.unsubscribe(this);
}