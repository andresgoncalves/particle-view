#ifndef TIME_SLIDER_WIDGET_H
#define TIME_SLIDER_WIDGET_H

#include <functional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>

#include "../controllers/AppContext.h"

class TimeSliderWidget : public QWidget
{
public:
  TimeSliderWidget(AppContext &appContext, QWidget *parent = nullptr);
  ~TimeSliderWidget();

private:
  bool wasPlaying = false;

  QSlider *slider;
  QLabel *timeLabel;

  AppContext &appContext;
};

#endif