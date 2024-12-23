#ifndef TIME_SLIDER_WIDGET_H
#define TIME_SLIDER_WIDGET_H

#include <functional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>

#include "../controllers/StoryController.h"

class TimeSliderWidget : public QWidget
{
public:
  TimeSliderWidget(StoryController &storyController, QWidget *parent = nullptr);

  void update();

private:
  QSlider *slider;
  QLabel *timeLabel;

  StoryController &storyController;
};

#endif