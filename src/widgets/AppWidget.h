#ifndef APP_WIDGET_H
#define APP_WIDGET_H

#include <QtWidgets/QWidget>

#include "GraphicsWidget.h"
#include "TimeSliderWidget.h"
#include "../controllers/RenderController.h"
#include "../controllers/StoryController.h"

class AppWidget : public QWidget
{
public:
  AppWidget(QWidget *parent = nullptr);

private:
  GraphicsWidget *graphicsWidget;
  TimeSliderWidget *timeSliderWidget;

  RenderController renderController;
  StoryController storyController;
};

#endif