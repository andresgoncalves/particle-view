#include <functional>

#include <QtWidgets/QHBoxLayout>

#include "TimeSliderWidget.h"
#include "GraphicsWidget.h"

TimeSliderWidget::TimeSliderWidget(StoryController &storyController, QWidget *parent) : QWidget{parent}, storyController{storyController}
{
  auto layout = new QHBoxLayout{this};
  layout->setContentsMargins({});

  auto font = this->font();
  font.setPointSize(16);

  timeLabel = new QLabel{"--"};
  timeLabel->setFont(font);
  timeLabel->setContentsMargins({});

  slider = new QSlider{Qt::Horizontal};
  slider->setRange(0, 100);

  layout->addWidget(slider, 1);
  layout->setAlignment(slider, Qt::AlignVCenter);
  layout->addWidget(timeLabel);
  layout->setAlignment(slider, Qt::AlignVCenter);

  connect(slider, &QSlider::valueChanged, this, [&](int)
          { storyController.setTime(storyController.getDuration() * slider->value() / 100.0); update(); });
}

void TimeSliderWidget::update()
{
  double time = storyController.getTime();
  double duration = storyController.getDuration();
  slider->setValue(time * 100.0 / duration);
  timeLabel->setText(QString::number(time, 'f', 3));
  QWidget::update();
}