#ifndef COLOR_SCALE_RENDERER_H
#define COLOR_SCALE_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <utils/color/GradientColorStrategy.h>

#include "Renderer.h"

/** Render color scale */
class ColorScaleRenderer : public Renderer<GradientColorStrategy>
{
public:
  /** Create axes renderer */
  ColorScaleRenderer();

  /** Render axes in viewport */
  void render(const GradientColorStrategy &gradientColorStrategy, const AppContext &appContext) override;
  /** Render axes in viewport */
  void render(const GradientColorStrategy &gradientColorStrategy, const AppContext &appContext, QPainter &painter, QSize viewportSize) override;
};

#endif