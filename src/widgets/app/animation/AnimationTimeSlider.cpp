#include "AnimationTimeSlider.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSlider>

AnimationTimeSlider::AnimationTimeSlider(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{parent}
{
  // Create slider
  auto timeSlider = new QSlider{Qt::Horizontal};
  timeSlider->setRange(0, 100);

  // Connect slider callbacks
  auto sliderMovedCallback = [&appContext](int value)
  {
    double duration = appContext.animationController.getDuration();
    double minTime = appContext.animationController.getFirstScene().time;
    appContext.animationController.setTime(minTime + duration * value / 100.0);
  };
  connect(timeSlider, &QSlider::sliderMoved, this, sliderMovedCallback);
  connect(timeSlider, &QSlider::sliderPressed, this,
          [=, this, &appContext]
          {
            wasPlaying = appContext.animationController.isPlaying();
            if (wasPlaying)
              appContext.animationController.pause();
            sliderMovedCallback(timeSlider->value());
          });
  connect(timeSlider, &QSlider::sliderReleased, this,
          [this, &appContext]
          {
            if (wasPlaying)
              appContext.animationController.play();
          });

  // Build layout
  auto layout = new QVBoxLayout{content};
  layout->addWidget(timeSlider);
  layout->setContentsMargins({});

  // Add time listener
  auto timeCallback = [=, &appContext](double time)
  {
    if (!timeSlider->isSliderDown())
    {
      double duration = appContext.animationController.getDuration();
      double minTime = appContext.animationController.getFirstScene().time;
      timeSlider->setValue((time - minTime) * 100.0 / duration);
    }
  };
  appContext.animationController.timeObservable.subscribe(this, timeCallback, true);
}

AnimationTimeSlider::~AnimationTimeSlider()
{
  appContext.animationController.timeObservable.unsubscribe(this);
}