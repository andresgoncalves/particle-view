#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QtWidgets>

#include "AppWidget.h"
#include "TimeSliderWidget.h"
#include "controls/SceneControlPanel.h"

AppWidget::AppWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  auto layout = new QHBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);

  graphicsWidget = new GraphicsWidget{appContext, this};
  graphicsWidget->setMinimumSize(400, 300);
  timeSliderWidget = new TimeSliderWidget{appContext};
  timeSliderWidget->setContentsMargins(12, 8, 12, 8);

  auto sceneControlPanel = new SceneControlPanel{appContext, this};

  auto rightSidebar = new QWidget{this};
  auto rightSidebarLayout = new QVBoxLayout{rightSidebar};
  auto rightSidebarLabel = new QLabel{"Right", rightSidebar};
  rightSidebarLayout->addWidget(rightSidebarLabel);
  rightSidebar->setLayout(rightSidebarLayout);

  auto toggleButton = new QPushButton{"Ver/Ocultar", this};

  connect(toggleButton, &QPushButton::clicked, this, [&](int)
          { appContext.viewController.toggleParticles(1); update(); });

  layout->addWidget(sceneControlPanel);

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
