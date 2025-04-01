#include "TimeAnimationControls.h"

#include <QtWidgets/QHBoxLayout>

TimeAnimationControls::TimeAnimationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Tiempo actual", parent}
{

  timeControl = new NumericControl{"Tiempo", this};
  connect(timeControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.storyController.setTime(timeControl->getLineEdit()->text().toFloat()); });
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

  timeCallback(appContext.storyController.timeObservable.get());
  playingCallback(appContext.storyController.playingObservable.get());

  appContext.storyController.timeObservable.subscribe(this, timeCallback);
  appContext.storyController.playingObservable.subscribe(this, playingCallback);
}

TimeAnimationControls::~TimeAnimationControls()
{
  appContext.storyController.timeObservable.unsubscribe(this);
  appContext.storyController.playingObservable.unsubscribe(this);
}