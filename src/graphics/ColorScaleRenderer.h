#ifndef COLOR_SCALE_RENDERER_H
#define COLOR_SCALE_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <utils/color/ColorScaleStrategy.h>

#include "Renderer.h"

/** Render color scale */
class ColorScaleRenderer : public Renderer<ColorScaleStrategy>
{
public:
  /** Create axes renderer */
  ColorScaleRenderer();

  /** Render axes in viewport */
  void render(const ColorScaleStrategy &gradientColorStrategy, const AppContext &appContext) override;
  /** Render axes in viewport */
  void render(const ColorScaleStrategy &gradientColorStrategy, const AppContext &appContext, QPainter &painter, QSize viewportSize) override;
};

#endif