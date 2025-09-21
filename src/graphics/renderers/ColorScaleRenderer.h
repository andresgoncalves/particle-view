#ifndef COLOR_SCALE_RENDERER_H
#define COLOR_SCALE_RENDERER_H

#include <QtCore/QRectF>

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <graphics/RenderContext.h>
#include <utils/color/ColorScaleStrategy.h>

#include "Renderer.h"

/** Color scale renderer */
class ColorScaleRenderer : protected Renderer
{
public:
  /** Create color scale renderer */
  ColorScaleRenderer();

  /** Render color scale */
  void render(const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext);

private:
  /** Paint color scale */
  void paintColorScale(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext);
  /** Paint labels */
  void paintLabels(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext);
};

#endif