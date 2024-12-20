#include "GraphicsWidget.h"
#include "../models/Particle.h"
#include "../models/Scene.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QOpenGLWidget{parent}, transformController{&renderController}
{
  qApp->installEventFilter(&eventFilter);
}

void GraphicsWidget::update()
{
  renderController.updateViewProjectionMatrix();
  QWidget::update();
}

void GraphicsWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  sceneRenderer = std::make_unique<SceneRenderer>();
  axisRenderer = std::make_unique<AxisRenderer>();
}

void GraphicsWidget::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
}

void GraphicsWidget::paintGL()
{
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sceneRenderer->render(scene, renderController);

  glClear(GL_DEPTH_BUFFER_BIT);

  axisRenderer->render(Axis::X, renderController);
  axisRenderer->render(Axis::Y, renderController);
  axisRenderer->render(Axis::Z, renderController);
}

void GraphicsWidget::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MouseButton::LeftButton)
  {
    transformController.start(screenToView(QVector2D{event->position()}));
  }
}

void GraphicsWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MouseButton::LeftButton)
  {
    transformController.end();
  }
}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (transformController.isTransforming())
  {
    TransformController::TransformType transformType;
    if (eventFilter.isKeyPressed(Qt::Key_T))
    {
      transformType = TransformController::Translation;
    }
    else if (eventFilter.isKeyPressed(Qt::Key_S))
    {
      transformType = TransformController::Scale;
    }
    else if (eventFilter.isKeyPressed(Qt::Key_Control))
    {
      transformType = TransformController::RotationZ;
    }
    else
    {
      transformType = TransformController::RotationXY;
    }

    transformController.move(screenToView(QVector2D{event->position()}), transformType);
    update();
  }
}

void GraphicsWidget::wheelEvent(QWheelEvent *event)
{
  transformController.scroll(event->angleDelta().y());
  update();
}

QVector2D GraphicsWidget::screenToView(const QVector2D &screenPoint) const
{
  auto viewPoint = QVector2D{(screenPoint.x() / window()->width()) * 2.0f - 1.0f,
                             1.0f - (screenPoint.y() / window()->height()) * 2.0f};
  return viewPoint;
}

bool GraphicsWidget::EventFilter::isKeyPressed(int key) const
{
  return pressedKeys.contains(key);
}

bool GraphicsWidget::EventFilter::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::KeyPress)
  {
    auto keyEvent = static_cast<QKeyEvent *>(event);
    pressedKeys.insert(keyEvent->key());
  }
  else if (event->type() == QEvent::KeyRelease)
  {
    auto keyEvent = static_cast<QKeyEvent *>(event);
    pressedKeys.erase(keyEvent->key());
  }
  return QObject::eventFilter(obj, event);
};