#include "ToolControls.h"

#include <functional>

#include <QtWidgets/QGridLayout>

ToolControls::ToolControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Modo de Transformación", parent}
{
  rotateXYButton = new QPushButton{"Rotate XY", this};
  rotateXYButton->setCheckable(true);
  connect(rotateXYButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.setTransformType(TransformController::TransformType::RotationXY); });
  rotateZButton = new QPushButton{"Rotate Z", this};
  rotateZButton->setCheckable(true);
  connect(rotateZButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.setTransformType(TransformController::TransformType::RotationZ); });
  translateXYButton = new QPushButton{"Translate XY", this};
  translateXYButton->setCheckable(true);
  connect(translateXYButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.setTransformType(TransformController::TransformType::TranslationXY); });
  translateZButton = new QPushButton{"Translate Z", this};
  translateZButton->setCheckable(true);
  connect(translateZButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.setTransformType(TransformController::TransformType::TranslationZ); });
  scaleButton = new QPushButton{"Scale", this};
  scaleButton->setCheckable(true);
  connect(scaleButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.setTransformType(TransformController::TransformType::Scale); });

  auto transformTypeCallback = [&](TransformController::TransformType value)
  {
    rotateXYButton->setChecked(value == TransformController::TransformType::RotationXY);
    rotateZButton->setChecked(value == TransformController::TransformType::RotationZ);
    translateXYButton->setChecked(value == TransformController::TransformType::TranslationXY);
    translateZButton->setChecked(value == TransformController::TransformType::TranslationZ);
    scaleButton->setChecked(value == TransformController::TransformType::Scale);
  };

  transformTypeCallback(appContext.transformController.getTransformType());

  appContext.transformController.transformTypeObservable.subscribe(this, transformTypeCallback);

  auto buttonLayout = new QGridLayout{content};
  buttonLayout->setHorizontalSpacing(4);
  buttonLayout->setVerticalSpacing(8);
  buttonLayout->addWidget(rotateXYButton, 0, 0);
  buttonLayout->addWidget(rotateZButton, 0, 1);
  buttonLayout->addWidget(translateXYButton, 1, 0);
  buttonLayout->addWidget(translateZButton, 1, 1);
  buttonLayout->addWidget(scaleButton, 2, 0, 1, 2);
}

ToolControls::~ToolControls()
{
  appContext.transformController.transformTypeObservable.unsubscribe(this);
}