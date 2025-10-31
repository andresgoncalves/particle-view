#include "SceneWidget.h"

#include <QtWidgets/QToolTip>

#include <models/Particle.h>
#include <models/Scene.h>

SceneWidget::SceneWidget(AppContext &appContext, QWidget *parent) : appContext{appContext}, QOpenGLWidget{parent}
{
  setMouseTracking(true);
  setFocusPolicy(Qt::FocusPolicy::StrongFocus);

  // Subscribe to triggers
  appContext.viewController.viewObservable.subscribe(this, [&]()
                                                     { update(); });
  appContext.animationController.timeObservable.subscribe(this, [&](double)
                                                          { update(); });
  appContext.animationController.storyObservable.subscribe(this, [&]()
                                                           { update(); });
  appContext.displayController.particleRuleObservable.subscribe(this, [&](auto)
                                                                { update(); });
  appContext.displayController.vectorRulesObservable.subscribe(this, [&](auto)
                                                               { update(); });
  appContext.displayController.customRulesObservable.subscribe(this, [&](auto)
                                                               { update(); });
  appContext.displayController.backgroundColorObservable.subscribe(this, [&](QColor color)
                                                                   { update(); });
  appContext.containerController.containersObservable.subscribe(this, [&](auto)
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
  timeRenderer = std::make_unique<TimeRenderer>();
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

  // Render scene
  sceneRenderer->render(scene, renderContext);

  // Render axes
  axesRenderer->render(renderContext);

  // Render time
  timeRenderer->render(appContext.animationController.getTime(), renderContext);

  // Render color scale
  if (auto colorScaleStrategy = dynamic_cast<ColorScaleStrategy *>(appContext.displayController.getParticleRule().getColorStrategy().get()))
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

  if (auto colorScaleStrategy = dynamic_cast<ColorScaleStrategy *>(appContext.displayController.getParticleRule().getColorStrategy().get()))
  {
    auto colorScaleValue = colorScaleRenderer->getValueAt(event->position(), *colorScaleStrategy, size());
    if (colorScaleValue.has_value())
    {
      auto rect = colorScaleRenderer->getRect(size());
      QToolTip::showText(event->globalPosition().toPoint(), QString::number(colorScaleValue.value(), 'f', 3), this, QRectF{mapToGlobal(rect.topLeft()), mapToGlobal(rect.bottomRight())}.toRect());
    }
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
