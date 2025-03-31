#include "TransformModesWidget.h"

#include <QtWidgets/QGridLayout>

TransformModesWidget::TransformModesWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  label = new QLabel{"Modo de transformación", this};

  rotateXYButton = new QPushButton{"Rotate XY", this};
  rotateXYButton->setCheckable(true);
  connect(rotateXYButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.transformType.set(TransformController::TransformType::RotationXY); });
  rotateZButton = new QPushButton{"Rotate Z", this};
  rotateZButton->setCheckable(true);
  connect(rotateZButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.transformType.set(TransformController::TransformType::RotationZ); });
  translateXYButton = new QPushButton{"Translate XY", this};
  translateXYButton->setCheckable(true);
  connect(translateXYButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.transformType.set(TransformController::TransformType::TranslationXY); });
  translateZButton = new QPushButton{"Translate Z", this};
  translateZButton->setCheckable(true);
  connect(translateZButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.transformType.set(TransformController::TransformType::TranslationZ); });
  scaleButton = new QPushButton{"Scale", this};
  scaleButton->setCheckable(true);
  connect(scaleButton, &QPushButton::clicked, this, [&]
          { appContext.transformController.transformType.set(TransformController::TransformType::Scale); });

  transformTypeCallback = [&](TransformController::TransformType value)
  {
    rotateXYButton->setChecked(value == TransformController::TransformType::RotationXY);
    rotateZButton->setChecked(value == TransformController::TransformType::RotationZ);
    translateXYButton->setChecked(value == TransformController::TransformType::TranslationXY);
    translateZButton->setChecked(value == TransformController::TransformType::TranslationZ);
    scaleButton->setChecked(value == TransformController::TransformType::Scale);
  };

  transformTypeCallback(appContext.transformController.transformType.get());

  appContext.transformController.transformType.subscribe(this, transformTypeCallback);

  auto layout = new QVBoxLayout{this};
  layout->addWidget(label);

  auto buttonLayout = new QGridLayout{};
  buttonLayout->setHorizontalSpacing(4);
  buttonLayout->setVerticalSpacing(8);
  buttonLayout->addWidget(rotateXYButton, 0, 0);
  buttonLayout->addWidget(rotateZButton, 0, 1);
  buttonLayout->addWidget(translateXYButton, 1, 0);
  buttonLayout->addWidget(translateZButton, 1, 1);
  buttonLayout->addWidget(scaleButton, 2, 0, 1, 2);
  layout->addLayout(buttonLayout);
}

TransformModesWidget::~TransformModesWidget()
{
  appContext.transformController.transformType.unsubscribe(this);
}