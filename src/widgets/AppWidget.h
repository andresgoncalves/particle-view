#ifndef APP_WIDGET_H
#define APP_WIDGET_H

#include <QtWidgets/QWidget>

#include "GraphicsWidget.h"
#include "TimeSliderWidget.h"
#include "../controllers/ViewController.h"
#include "../controllers/StoryController.h"
#include "../controllers/TransformController.h"

class AppWidget : public QWidget
{
public:
  AppWidget(QWidget *parent = nullptr);

  ViewController *getViewController();
  StoryController *getStoryController();

private:
  GraphicsWidget *graphicsWidget;
  TimeSliderWidget *timeSliderWidget;

  ViewController viewController;
  StoryController storyController;
  TransformController transformController;
};

#endif