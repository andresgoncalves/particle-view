#include "GraphicsWidget.h"
#include "../models/Particle.h"
#include "../models/Scene.h"

GraphicsWidget::GraphicsWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QOpenGLWidget{parent}
{
  eventFilter.addListener(Qt::Key_O, [&]()
                          { appContext.viewController.projectionMode = ViewController::Ortho; update(); });
  eventFilter.addListener(Qt::Key_P, [&]()
                          { appContext.viewController.projectionMode = ViewController::Perspective; update(); });
  eventFilter.addListener(Qt::Key_K, [&]()
                          { appContext.viewController.particleShape = ViewController::Skeleton; update(); });
  eventFilter.addListener(Qt::Key_L, [&]()
                          { appContext.viewController.particleShape = ViewController::Solid; update(); });
  eventFilter.addListener(Qt::Key_Space, [&]()
                          { if(appContext.animationController.isPlaying()) appContext.animationController.pause(); else appContext.animationController.play(); });
  eventFilter.addListener(Qt::Key_E, [&]()
                          { appContext.animationController.reset(); update(); });
  eventFilter.addListener(Qt::Key_Left, [&]()
                          { appContext.animationController.skip(-0.1); update(); });
  eventFilter.addListener(Qt::Key_Right, [&]()
                          { appContext.animationController.skip(0.1); update(); });

  eventFilter.addListener(Qt::Key_T, [&]()
                          {
                            if (appContext.viewController.projectionMode == ViewController::Perspective)
                            {
                              appContext.transformController.setTransformType(eventFilter.isKeyPressed(Qt::Key_Control) ? TransformController::TranslationZ : TransformController::TranslationXY);
                            } else if( eventFilter.isKeyPressed(Qt::Key_Control) ){
                              appContext.transformController.setTransformType(TransformController::Scale);
                            } });
  eventFilter.addListener(Qt::Key_S, [&]()
                          { appContext.transformController.setTransformType(TransformController::Scale); });
  eventFilter.addListener(Qt::Key_R,
                          [&]()
                          {
                            if (eventFilter.isKeyPressed(Qt::Key_Control))
                            {
                              appContext.transformController.setTransformType(TransformController::RotationZ);
                            }
                            else
                            {
                              appContext.transformController.setTransformType(TransformController::RotationXY);
                            }
                          });

  qApp->installEventFilter(&eventFilter);

  appContext.animationController.timeObservable.subscribe(this, [&](double)
                                                          { update(); });
}

void GraphicsWidget::update()
{
  appContext.viewController.updateViewProjectionMatrix();
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
    appContext.viewController.setViewport({1.0f, static_cast<float>(height) / width});
  else
    appContext.viewController.setViewport({static_cast<float>(width) / height, 1.0f});

  update();
}

void GraphicsWidget::paintGL()
{
  auto scene = appContext.animationController.getScene();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sceneRenderer->render(scene, appContext);

  glClear(GL_DEPTH_BUFFER_BIT);

  axisRenderer->render(Axis::X, appContext);
  axisRenderer->render(Axis::Y, appContext);
  axisRenderer->render(Axis::Z, appContext);
}

void GraphicsWidget::mousePressEvent(QMouseEvent *event)
{
  setFocus();
  if (event->button() == Qt::MouseButton::LeftButton)
  {
    appContext.transformController.start(screenToView(QVector2D{event->position()}));
  }
}

void GraphicsWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MouseButton::LeftButton)
  {
    appContext.transformController.end();
  }
}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (appContext.transformController.isTransforming())
  {
    appContext.transformController.move(screenToView(QVector2D{event->position()}));
    update();
  }
}

void GraphicsWidget::wheelEvent(QWheelEvent *event)
{
  appContext.transformController.scroll(-event->angleDelta().y());
  update();
}

QVector2D GraphicsWidget::screenToView(const QVector2D &screenPoint) const
{
  auto viewPoint = appContext.viewController.getViewport() *
                   QVector2D{
                       (screenPoint.x() / window()->width()) * 2.0f - 1.0f,
                       1.0f - (screenPoint.y() / window()->height()) * 2.0f};
  return viewPoint;
}
