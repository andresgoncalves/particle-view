#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "AppWidget.h"
#include "TimeSliderWidget.h"

inline Story _createStoryMock();

AppWidget::AppWidget(QWidget *parent) : QWidget{parent}
{
  storyController.story = _createStoryMock();

  auto layout = new QVBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);

  auto font = this->font();
  font.setPointSize(24);

  auto label = new QLabel{"Hello, from particle-view!"};
  label->setFont(font);
  label->setContentsMargins(24, 16, 24, 16);
  graphicsWidget = new GraphicsWidget{storyController, renderController};
  graphicsWidget->setMinimumSize(400, 300);
  timeSliderWidget = new TimeSliderWidget{storyController};
  timeSliderWidget->setContentsMargins(12, 8, 12, 8);

  layout->addWidget(label);
  layout->setAlignment(label, Qt::AlignCenter);
  layout->addWidget(graphicsWidget, 1);
  layout->addWidget(timeSliderWidget);

  setLayout(layout);
  adjustSize();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [&]()
          { graphicsWidget->update(); timeSliderWidget->update(); });
  timer->start(1.0 / 60.0);
}

inline Story _createStoryMock()
{
  auto story = Story{};
  auto scene = Scene{};
  auto particle = Particle{};

  particle.position = {0.5f, 0.0f, 0.0f};
  particle.color = {1.0f, 0.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.5f, 0.0f};
  particle.color = {0.0f, 1.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.0f, 0.5f};
  particle.color = {0.0f, 0.0f, 1.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.0f, 0.0f};
  particle.color = {1.0f, 1.0f, 1.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  story.scenes.insert(std::make_pair(0.0, scene));
  scene.particles.clear();

  particle.position = {0.2f, 0.0f, 0.0f};
  particle.color = {1.0f, 0.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.2f, 0.0f};
  particle.color = {0.0f, 1.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.0f, 0.2f};
  particle.color = {0.0f, 0.0f, 1.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.0f, 0.0f};
  particle.color = {1.0f, 1.0f, 1.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  story.scenes.insert(std::make_pair(1.0, scene));
  scene.particles.clear();

  particle.position = {0.1f, 0.0f, 0.0f};
  particle.color = {1.0f, 0.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.1f, 0.0f};
  particle.color = {0.0f, 1.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.0f, 0.1f};
  particle.color = {0.0f, 0.0f, 1.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {0.0f, 0.0f, 0.0f};
  particle.color = {1.0f, 1.0f, 1.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  story.scenes.insert(std::make_pair(2.0, scene));

  return story;
}
