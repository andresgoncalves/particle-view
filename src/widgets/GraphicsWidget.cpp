#include "GraphicsWidget.h"
#include "../models/Particle.h"
#include "../models/Scene.h"

GraphicsWidget::GraphicsWidget(StoryController &storyController, ViewController &viewController, TransformController &transformController, QWidget *parent) : storyController{storyController}, viewController{viewController}, transformController{transformController}, QOpenGLWidget{parent}
{
  eventFilter.addListener(Qt::Key_O, [&]()
                          { viewController.projectionMode = ViewController::Ortho; update(); });
  eventFilter.addListener(Qt::Key_P, [&]()
                          { viewController.projectionMode = ViewController::Perspective; update(); });
  eventFilter.addListener(Qt::Key_K, [&]()
                          { viewController.particleShape = ViewController::Skeleton; update(); });
  eventFilter.addListener(Qt::Key_L, [&]()
                          { viewController.particleShape = ViewController::Solid; update(); });
  eventFilter.addListener(Qt::Key_Space, [&]()
                          { if(storyController.isPlaying()) storyController.pause(); else storyController.play(); });
  eventFilter.addListener(Qt::Key_R, [&]()
                          { storyController.reset(); update(); });
  eventFilter.addListener(Qt::Key_Left, [&]()
                          { storyController.skip(-0.1); update(); });
  eventFilter.addListener(Qt::Key_Right, [&]()
                          { storyController.skip(0.1); update(); });

  eventFilter.addListener(Qt::Key_T, [&]()
                          {
                            if (viewController.projectionMode == ViewController::Perspective)
                            {
                              transformController.transformType = eventFilter.isKeyPressed(Qt::Key_Control) ? TransformController::TranslationZ : TransformController::TranslationXY;
                            } else if( eventFilter.isKeyPressed(Qt::Key_Control) ){
                              transformController.transformType = TransformController::Scale;
                            } });
  eventFilter.addListener(Qt::Key_S, [&]()
                          { transformController.transformType = TransformController::Scale; });
  eventFilter.addListener(Qt::Key_R,
                          [&]()
                          {
                            if (eventFilter.isKeyPressed(Qt::Key_Control))
                            {
                              transformController.transformType = TransformController::RotationZ;
                            }
                            else
                            {
                              transformController.transformType = TransformController::RotationXY;
                            }
                          });

  qApp->installEventFilter(&eventFilter);
}

void GraphicsWidget::update()
{
  viewController.updateViewProjectionMatrix();
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
    viewController.setViewport({1.0f, static_cast<float>(height) / width});
  else
    viewController.setViewport({static_cast<float>(width) / height, 1.0f});

  update();
}

void GraphicsWidget::paintGL()
{
  auto [time, scene] = storyController.getScene();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sceneRenderer->render(scene, viewController);

  glClear(GL_DEPTH_BUFFER_BIT);

  axisRenderer->render(Axis::X, viewController);
  axisRenderer->render(Axis::Y, viewController);
  axisRenderer->render(Axis::Z, viewController);
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
    transformController.move(screenToView(QVector2D{event->position()}));
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
  auto viewPoint = viewController.getViewport() *
                   QVector2D{
                       (screenPoint.x() / window()->width()) * 2.0f - 1.0f,
                       1.0f - (screenPoint.y() / window()->height()) * 2.0f};
  return viewPoint;
}
