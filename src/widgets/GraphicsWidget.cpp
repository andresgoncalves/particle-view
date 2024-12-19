#include "GraphicsWidget.h"
#include "../models/Particle.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QOpenGLWidget{parent} {}

void GraphicsWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  particleRenderer = std::make_unique<ParticleRenderer>();
}

void GraphicsWidget::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
}

void GraphicsWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);

  auto particle1 = Particle{};
  particle1.position = {0.5f, 0.5f, 0.0f};
  particle1.color = {0.0f, 1.0f, 0.0f};
  particle1.radius = 0.1f;

  auto particle2 = Particle{};
  particle2.position = {-0.5f, 0.0f, 0.0f};
  particle2.color = {1.0f, 0.0f, 0.0f};
  particle2.radius = 0.1f;

  particleRenderer->render(particle1);
  particleRenderer->render(particle2);
}
