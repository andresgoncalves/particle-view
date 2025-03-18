#ifndef GRAPHICS_WIDGET_H
#define GRAPHICS_WIDGET_H

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMouseEvent>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "utils/KeyEventFilter.h"
#include "../controllers/ViewController.h"
#include "../controllers/StoryController.h"
#include "../controllers/TransformController.h"
#include "../graphics/AxisRenderer.h"
#include "../graphics/SceneRenderer.h"

class GraphicsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
  GraphicsWidget(StoryController &storyController, ViewController &viewController, TransformController &transformController, QWidget *parent = nullptr);

  void update();

protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

private:
  QVector2D screenToView(const QVector2D &point) const;

  KeyEventFilter eventFilter;
  std::unique_ptr<AxisRenderer>
      axisRenderer;
  std::unique_ptr<SceneRenderer>
      sceneRenderer;

  TransformController &transformController;
  ViewController &viewController;
  StoryController &storyController;
};

#endif