#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QtWidgets>

#include "AppWidget.h"
#include "TimeSliderWidget.h"
#include "controls/SceneControlPanel.h"

AppWidget::AppWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  graphicsWidget = new GraphicsWidget{appContext, this};
  graphicsWidget->setMinimumSize(400, 300);
  timeSliderWidget = new TimeSliderWidget{appContext};
  timeSliderWidget->setContentsMargins(12, 8, 12, 8);

  auto toggleButton = new QPushButton{"Ver/Ocultar", this};

  connect(toggleButton, &QPushButton::clicked, this, [&](int)
          { appContext.viewController.toggleParticles(1); update(); });

  auto layout = new QVBoxLayout{this};
  layout->addWidget(graphicsWidget, 1);
  layout->addWidget(timeSliderWidget);
  layout->addWidget(toggleButton);
  layout->setContentsMargins({});

  adjustSize();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [&]()
          { if(appContext.animationController.isPlaying()) appContext.animationController.updateTime(); });

  timer->start(1.0 / 60.0);
}
