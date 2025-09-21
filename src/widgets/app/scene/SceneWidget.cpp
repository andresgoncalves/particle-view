#include "SceneWidget.h"

#include <models/Particle.h>
#include <models/Scene.h>

SceneWidget::SceneWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QOpenGLWidget{parent}
{
  // Subscribe to triggers
  appContext.viewController.viewObservable.subscribe(this, [&]()
                                                     { update(); });
  appContext.animationController.timeObservable.subscribe(this, [&](double)
                                                          { update(); });
  appContext.animationController.storyObservable.subscribe(this, [&]()
                                                           { update(); });
  appContext.displayController.displayParticlesObservable.subscribe(this, [&](DisplayController::DisplayProperty)
                                                                    { update(); });
  appContext.displayController.displayVectorsObservable.subscribe(this, [&](std::map<std::string, DisplayController::DisplayProperty>)
                                                                  { update(); });
  appContext.displayController.displayRulesObservable.subscribe(this, [&]()
                                                                { update(); });
  appContext.displayController.backgroundColorObservable.subscribe(this, [&](QColor color)
                                                                   { update(); });
}

void SceneWidget::update()
{
  appContext.viewController.updateViewProjectionMatrix();
  QWidget::update();
}

void SceneWidget::initializeGL()
{
  // Initialize GL
  initializeOpenGLFunctions();
  glDepthFunc(GL_LESS);

  // Set default renderers
  sceneRenderer = std::make_unique<SceneRenderer>();
  axesRenderer = std::make_unique<AxesRenderer>();
  colorScaleRenderer = std::make_unique<ColorScaleRenderer>();
}

void SceneWidget::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);

  // Scale viewport with longest side equal to 1
  if (width > height)
    appContext.viewController.setViewport({1.0f, static_cast<float>(height) / width});
  else
    appContext.viewController.setViewport({static_cast<float>(width) / height, 1.0f});

  update();
}

void SceneWidget::paintGL()
{
  // Get scene
  auto scene = appContext.animationController.getScene();

  // Get render context
  auto painter = QPainter{this};
  auto renderContext = RenderContext{
      size(),
      painter,
      appContext,
  };

  // Clear buffers
  painter.beginNativePainting();
  glClearColor(
      appContext.displayController.getBackgroundColor().redF(),
      appContext.displayController.getBackgroundColor().greenF(),
      appContext.displayController.getBackgroundColor().blueF(),
      1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  painter.endNativePainting();

  // Render scene
  sceneRenderer->render(scene, renderContext);

  // Render axes
  axesRenderer->render(renderContext);

  // Render color scale
  if (auto colorScaleStrategy = dynamic_cast<ColorScaleStrategy *>(appContext.displayController.getDisplayParticles().second.get()))
    colorScaleRenderer->render(*colorScaleStrategy, renderContext);
}

void SceneWidget::mousePressEvent(QMouseEvent *event)
{
  setFocus();

  if (event->button() == Qt::MouseButton::LeftButton)
    appContext.transformController.start(screenToView(QVector2D{event->position()}));
}

void SceneWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MouseButton::LeftButton)
    appContext.transformController.end();
}

void SceneWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (appContext.transformController.isTransforming())
  {
    appContext.transformController.move(screenToView(QVector2D{event->position()}));
    update();
  }
}

void SceneWidget::wheelEvent(QWheelEvent *event)
{
  appContext.transformController.scroll(-event->angleDelta().y());
  update();
}

QVector2D SceneWidget::screenToView(const QVector2D &screenPoint) const
{
  auto viewPoint = appContext.viewController.getViewport() *
                   QVector2D{
                       (screenPoint.x() / window()->width()) * 2.0f - 1.0f,
                       1.0f - (screenPoint.y() / window()->height()) * 2.0f};
  return viewPoint;
}
