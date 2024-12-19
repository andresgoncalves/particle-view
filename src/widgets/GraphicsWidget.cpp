#include "GraphicsWidget.h"
#include "../models/Particle.h"
#include "../models/Scene.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QOpenGLWidget{parent}
{
  renderController = std::make_unique<RenderController>();
}

void GraphicsWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  sceneRenderer = std::make_unique<SceneRenderer>();
}

void GraphicsWidget::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
}

void GraphicsWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);

  auto scene = Scene{};

  auto particle = Particle{};
  particle.position = {0.5f, 0.0f, 0.0f};
  particle.color = {0.0f, 1.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  particle.position = {-0.5f, 0.0f, 0.0f};
  particle.color = {1.0f, 0.0f, 0.0f};
  particle.radius = 0.1f;
  scene.particles.push_back(particle);

  sceneRenderer->render(scene, *renderController);
}

void GraphicsWidget::mousePressEvent(QMouseEvent *event) {}

void GraphicsWidget::mouseReleaseEvent(QMouseEvent *event) {}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *event) {}
