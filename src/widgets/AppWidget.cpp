#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QtWidgets>

#include "AppWidget.h"
#include "TimeSliderWidget.h"
#include "ToolPanelWidget.h"

AppWidget::AppWidget(QWidget *parent) : transformController{viewController}, QWidget{parent}
{
  auto layout = new QHBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);

  graphicsWidget = new GraphicsWidget{storyController, viewController, transformController, this};
  graphicsWidget->setMinimumSize(400, 300);
  timeSliderWidget = new TimeSliderWidget{storyController};
  timeSliderWidget->setContentsMargins(12, 8, 12, 8);

  auto toolPanelWidget = new ToolPanelWidget{transformController, this};

  auto rightSidebar = new QWidget{this};
  auto rightSidebarLayout = new QVBoxLayout{rightSidebar};
  auto rightSidebarLabel = new QLabel{"Right", rightSidebar};
  rightSidebarLayout->addWidget(rightSidebarLabel);
  rightSidebar->setLayout(rightSidebarLayout);

  auto toggleButton = new QPushButton{"Ver/Ocultar", this};

  connect(toggleButton, &QPushButton::clicked, this, [&](int)
          { viewController.toggleParticles(1); update(); });

  layout->addWidget(toolPanelWidget);

  auto centerLayout = new QVBoxLayout{};
  centerLayout->addWidget(graphicsWidget, 1);
  centerLayout->addWidget(timeSliderWidget);
  centerLayout->addWidget(toggleButton);
  layout->addLayout(centerLayout, 1);

  layout->addWidget(rightSidebar);

  adjustSize();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [&]()
          { graphicsWidget->update(); timeSliderWidget->update(); });
  timer->start(1.0 / 60.0);
}

ViewController *AppWidget::getViewController()
{
  return &viewController;
}

StoryController *AppWidget::getStoryController()
{
  return &storyController;
}
