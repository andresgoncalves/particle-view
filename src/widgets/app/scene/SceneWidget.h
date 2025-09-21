#ifndef SCENE_WIDGET_H
#define SCENE_WIDGET_H

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMouseEvent>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include <graphics/renderers/AxesRenderer.h>
#include <graphics/renderers/SceneRenderer.h>
#include <graphics/renderers/ColorScaleRenderer.h>
#include <controllers/AppContext.h>
#include <models/Scene.h>
#include <utils/color/ColorScaleStrategy.h>

/** Widget where the scene is rendered */
class SceneWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
  /** Creates the scene widget */
  SceneWidget(AppContext &appContext, QWidget *parent = nullptr);

  /** Triggers an update */
  void update();

protected:
  /** Initializes OpenGL context */
  void initializeGL() override;
  /** Handles widget resize */
  void resizeGL(int width, int height) override;
  /** Renders current frame */
  void paintGL() override;

  /** Handles mouse press with TransformController */
  void mousePressEvent(QMouseEvent *event) override;
  /** Handles mouse release with TransformController */
  void mouseReleaseEvent(QMouseEvent *event) override;
  /** Handles mouse move with TransformController */
  void mouseMoveEvent(QMouseEvent *event) override;
  /** Handles mouse scroll with TransformController */
  void wheelEvent(QWheelEvent *event) override;

private:
  /** Maps screen coordinates to view coordinates */
  QVector2D screenToView(const QVector2D &point) const;

  /** Renderer used for drawing axes */
  std::unique_ptr<AxesRenderer>
      axesRenderer;
  /** Renderer used for drawing scene */
  std::unique_ptr<SceneRenderer>
      sceneRenderer;
  /** Renderer used for drawing color scale */
  std::unique_ptr<ColorScaleRenderer>
      colorScaleRenderer;

  /** Application context */
  AppContext &appContext;
};

#endif