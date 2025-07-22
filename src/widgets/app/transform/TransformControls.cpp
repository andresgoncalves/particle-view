#include "TransformControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

TransformControls::TransformControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Transformación", parent}
{
  // Rotate button
  auto rotateButton = new QPushButton{"Rotar", this};
  rotateButton->setCheckable(true);
  connect(rotateButton, &QPushButton::clicked, this, [&appContext]
          { appContext.transformController.setTransformType(TransformController::TransformType::Rotation); });

  // Translate button
  auto translateButton = new QPushButton{"Trasladar", this};
  translateButton->setCheckable(true);
  connect(translateButton, &QPushButton::clicked, this, [&appContext]
          { appContext.transformController.setTransformType(TransformController::TransformType::Translation); });

  // Scale button
  auto scaleButton = new QPushButton{"Escalar", this};
  scaleButton->setCheckable(true);
  connect(scaleButton, &QPushButton::clicked, this, [&appContext]
          { appContext.transformController.setTransformType(TransformController::TransformType::Scale); });

  // Build layout
  auto buttonLayout = new QGridLayout{content};
  buttonLayout->addWidget(rotateButton, 0, 0);
  buttonLayout->addWidget(translateButton, 0, 1);
  buttonLayout->addWidget(scaleButton, 1, 0);
  buttonLayout->setHorizontalSpacing(4);
  buttonLayout->setVerticalSpacing(8);
  buttonLayout->setContentsMargins({});

  // Add transform type listener
  auto transformTypeCallback = [=](TransformController::TransformType value)
  {
    rotateButton->setChecked(value == TransformController::TransformType::Rotation);
    translateButton->setChecked(value == TransformController::TransformType::Translation);
    scaleButton->setChecked(value == TransformController::TransformType::Scale);
  };
  appContext.transformController.transformTypeObservable.subscribe(this, transformTypeCallback, true);
}

TransformControls::~TransformControls()
{
  appContext.transformController.transformTypeObservable.unsubscribe(this);
}