#ifndef GRAPHICS_WIDGET_H
#define GRAPHICS_WIDGET_H

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMouseEvent>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "../controllers/RenderController.h"
#include "../graphics/SceneRenderer.h"

class GraphicsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
  GraphicsWidget(QWidget *parent = nullptr);

protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  std::unique_ptr<RenderController> renderController;
  std::unique_ptr<SceneRenderer>
      sceneRenderer;
};

#endif