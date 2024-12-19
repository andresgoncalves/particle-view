#ifndef GRAPHICS_WIDGET_H
#define GRAPHICS_WIDGET_H

#include <QtGui/QOpenGLFunctions>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "../graphics/ParticleRenderer.h"

class GraphicsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
  GraphicsWidget(QWidget *parent = nullptr);

protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

private:
  std::unique_ptr<ParticleRenderer> particleRenderer;
};

#endif