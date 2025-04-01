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

  connect(slider, &QSlider::valueChanged, this, [&](int)
          { appContext.storyController.setTime(appContext.storyController.getDuration() * slider->value() / 100.0); });

  auto timeCallback = [&](double time)
  {
    double duration = appContext.storyController.getDuration();
    slider->setValue(time * 100.0 / duration);
    timeLabel->setText(QString::number(time, 'f', 3));
  };

  appContext.storyController.timeObservable.subscribe(this, timeCallback);
}

TimeSliderWidget::~TimeSliderWidget()
{
  appContext.storyController.timeObservable.unsubscribe(this);
}
