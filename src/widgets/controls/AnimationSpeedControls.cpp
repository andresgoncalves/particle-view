#include "AnimationSpeedControls.h"

#include <QtWidgets/QHBoxLayout>

AnimationSpeedControls::AnimationSpeedControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Velocidad de reproducción", parent}
{
  animationSpeedControl = new NumericControl{this};
  connect(animationSpeedControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.animationController.setAnimationSpeed(animationSpeedControl->getLineEdit()->text().toFloat()); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(animationSpeedControl);
  layout->setContentsMargins({});

  auto animationSpeedCallback = [&](double value)
  {
    animationSpeedControl->getLineEdit()->setText(QString::number(value, 'f', 3));
  };

  animationSpeedCallback(appContext.animationController.animationSpeedObservable.get());

  appContext.animationController.animationSpeedObservable.subscribe(this, animationSpeedCallback);
}

AnimationSpeedControls::~AnimationSpeedControls()
{
  appContext.animationController.animationSpeedObservable.unsubscribe(this);
}