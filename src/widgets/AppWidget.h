#ifndef APP_WIDGET_H
#define APP_WIDGET_H

#include <QtWidgets/QWidget>

#include "GraphicsWidget.h"
#include "TimeSliderWidget.h"
#include "../controllers/AppContext.h"

class AppWidget : public QWidget
{
public:
  AppWidget(AppContext &appContext, QWidget *parent = nullptr);

private:
  GraphicsWidget *graphicsWidget;
  TimeSliderWidget *timeSliderWidget;

  AppContext &appContext;
};

#endif