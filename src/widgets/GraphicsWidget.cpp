#include <QtCore/QTimer>

#include "GraphicsWidget.h"
#include "../models/Particle.h"
#include "../models/Scene.h"

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

GraphicsWidget::GraphicsWidget(QWidget *parent) : QOpenGLWidget{parent}, transformController{&renderController}
{
  eventFilter.addListener(Qt::Key_O, [&]()
                          { renderController.projectionMode = RenderController::Ortho; update(); });
  eventFilter.addListener(Qt::Key_P, [&]()
                          { renderController.projectionMode = RenderController::Perspective; update(); });
  eventFilter.addListener(Qt::Key_K, [&]()
                          { renderController.particleShape = RenderController::Skeleton; update(); });
  eventFilter.addListener(Qt::Key_L, [&]()
                          { renderController.particleShape = RenderController::Solid; update(); });
  eventFilter.addListener(Qt::Key_Space, [&]()
                          { if(storyController.isPlaying()) storyController.pause(); else storyController.play(); });
  eventFilter.addListener(Qt::Key_R, [&]()
                          { storyController.reset(); update(); });
  eventFilter.addListener(Qt::Key_Left, [&]()
                          { storyController.skip(-0.1); update(); }, KeyEventFilter::Multi);
  eventFilter.addListener(Qt::Key_Right, [&]()
                          { storyController.skip(0.1); update(); }, KeyEventFilter::Multi);
  installEventFilter(&eventFilter);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [&]()
          { update(); });
  timer->start(1.0 / 60.0);

  storyController.story = _createStoryMock();
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

  if (width > height)
    renderController.setViewport({1.0f, static_cast<float>(height) / width});
  else
    renderController.setViewport({static_cast<float>(width) / height, 1.0f});

  update();
}

void GraphicsWidget::paintGL()
{
  auto [time, scene] = storyController.getScene();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sceneRenderer->render(scene, renderController);

  glClear(GL_DEPTH_BUFFER_BIT);

  axisRenderer->render(Axis::X, renderController);
  axisRenderer->render(Axis::Y, renderController);
  axisRenderer->render(Axis::Z, renderController);
}

void GraphicsWidget::mousePressEvent(QMouseEvent *event)
{
  setFocus();
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
    if (eventFilter.isKeyPressed(Qt::Key_T) && renderController.projectionMode == RenderController::Perspective)
    {
      transformType = eventFilter.isKeyPressed(Qt::Key_Control) ? TransformController::TranslationZ : TransformController::TranslationXY;
    }
    else if (eventFilter.isKeyPressed(Qt::Key_S) || eventFilter.isKeyPressed(Qt::Key_T) && eventFilter.isKeyPressed(Qt::Key_Control) && renderController.projectionMode == RenderController::Ortho)
    {
      transformType = TransformController::Scale;
    }
    else
    {
      transformType = eventFilter.isKeyPressed(Qt::Key_Control) ? TransformController::RotationZ : TransformController::RotationXY;
    }

    transformController.move(screenToView(QVector2D{event->position()}), transformType);
    update();
  }
}

void GraphicsWidget::wheelEvent(QWheelEvent *event)
{
  transformController.scroll(-event->angleDelta().y());
  update();
}

QVector2D GraphicsWidget::screenToView(const QVector2D &screenPoint) const
{
  auto viewPoint = renderController.getViewport() *
                   QVector2D{
                       (screenPoint.x() / window()->width()) * 2.0f - 1.0f,
                       1.0f - (screenPoint.y() / window()->height()) * 2.0f};
  return viewPoint;
}
