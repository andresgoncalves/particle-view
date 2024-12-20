#ifndef GRAPHICS_WIDGET_H
#define GRAPHICS_WIDGET_H

#include <set>

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMouseEvent>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "../controllers/RenderController.h"
#include "../controllers/TransformController.h"
#include "../graphics/SceneRenderer.h"

class GraphicsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
  GraphicsWidget(QWidget *parent = nullptr);

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
  class EventFilter : public QObject
  {
  public:
    bool isKeyPressed(int key) const;

  protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

  private:
    std::set<int> pressedKeys;
  };

  QVector2D screenToView(QVector2D point);

  EventFilter eventFilter;
  RenderController renderController;
  TransformController transformController;
  std::unique_ptr<SceneRenderer>
      sceneRenderer;
};

#endif