#include <functional>

#include <QtWidgets/QHBoxLayout>

#include "TimeSliderWidget.h"
#include "GraphicsWidget.h"

TimeSliderWidget::TimeSliderWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{

  auto font = this->font();
  font.setPointSize(16);

  timeLabel = new QLabel{"--"};
  timeLabel->setFont(font);
  timeLabel->setAlignment(Qt::AlignRight);
  timeLabel->setMinimumSize(64, 0);
  timeLabel->setMaximumSize(64, std::numeric_limits<short>::max());
  timeLabel->setContentsMargins({});

  slider = new QSlider{Qt::Horizontal};
  slider->setRange(0, 100);

  auto layout = new QHBoxLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(slider, 1);
  layout->addWidget(timeLabel);
  layout->setContentsMargins({});

  auto sliderMovedCallback = [&](int value)
  {
    double duration = appContext.animationController.getDuration();
    double minTime = appContext.animationController.getFirstScene().time;
    appContext.animationController.setTime(minTime + duration * value / 100.0);
  };

  auto sliderPressedCallback = [&, sliderMovedCallback = sliderMovedCallback]
  {
    if (appContext.animationController.isPlaying())
    {
      wasPlaying = true;
      appContext.animationController.pause();
    }
    sliderMovedCallback(slider->value());
  };

  auto sliderReleasedCallback = [&]
  {
    if (wasPlaying)
    {
      wasPlaying = false;
      appContext.animationController.play();
    }
  };

  connect(slider, &QSlider::sliderPressed, this, sliderPressedCallback);
  connect(slider, &QSlider::sliderReleased, this, sliderReleasedCallback);
  connect(slider, &QSlider::sliderMoved, this, sliderMovedCallback);

  auto timeCallback = [&](double time)
  {
    if (!slider->isSliderDown())
    {
      double duration = appContext.animationController.getDuration();
      double minTime = appContext.animationController.getFirstScene().time;
      slider->setValue((time - minTime) * 100.0 / duration);
    }
    timeLabel->setText(QString::number(time, 'f', 3));
  };

  timeCallback(appContext.animationController.getTime());

  appContext.animationController.timeObservable.subscribe(this, timeCallback);
}

TimeSliderWidget::~TimeSliderWidget()
{
  appContext.animationController.timeObservable.unsubscribe(this);
}
