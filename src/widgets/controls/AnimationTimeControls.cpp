#include "AnimationTimeControls.h"

#include <QtWidgets/QHBoxLayout>

AnimationTimeControls::AnimationTimeControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Tiempo actual", parent}
{

  timeControl = new NumericControl{"Tiempo", this};
  connect(timeControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.animationController.setTime(timeControl->getLineEdit()->text().toFloat()); });
  // frameControl = new NumericControl{"Frame", this};
  // connect(frameControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
  //         { appContext.viewController.setScale(frameControl->getLineEdit()->text().toFloat()); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(timeControl);
  // layout->addWidget(frameControl);
  layout->setContentsMargins({});

  auto timeCallback = [&](double value)
  {
    timeControl->getLineEdit()->setText(QString::number(value, 'f', 3));
  };

  auto playingCallback = [&](bool value)
  {
    timeControl->getLineEdit()->setDisabled(value);
  };

  timeCallback(appContext.animationController.timeObservable.get());
  playingCallback(appContext.animationController.playingObservable.get());

  appContext.animationController.timeObservable.subscribe(this, timeCallback);
  appContext.animationController.playingObservable.subscribe(this, playingCallback);
}

AnimationTimeControls::~AnimationTimeControls()
{
  appContext.animationController.timeObservable.unsubscribe(this);
  appContext.animationController.playingObservable.unsubscribe(this);
}