#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QtWidgets>

#include "AppWidget.h"
#include "TimeSliderWidget.h"

AppWidget::AppWidget(QWidget *parent) : QWidget{parent}
{
  auto layout = new QVBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);

  graphicsWidget = new GraphicsWidget{storyController, renderController};
  graphicsWidget->setMinimumSize(400, 300);
  timeSliderWidget = new TimeSliderWidget{storyController};
  timeSliderWidget->setContentsMargins(12, 8, 12, 8);

  auto toggleButton = new QPushButton{"Ver/Ocultar", this};

  connect(toggleButton, &QPushButton::clicked, this, [&](int)
          { renderController.toggleParticles(1); update(); });

  layout->addWidget(graphicsWidget, 1);
  layout->addWidget(timeSliderWidget);
  layout->addWidget(toggleButton);

  setLayout(layout);
  adjustSize();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [&]()
          { graphicsWidget->update(); timeSliderWidget->update(); });
  timer->start(1.0 / 60.0);
}

RenderController *AppWidget::getRenderController()
{
  return &renderController;
}

StoryController *AppWidget::getStoryController()
{
  return &storyController;
}
