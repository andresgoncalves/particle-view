#ifndef COLOR_SCALE_RENDERER_H
#define COLOR_SCALE_RENDERER_H

#include <optional>

#include <QtCore/QPointF>
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

  /** Get value at point */
  std::optional<float> getValueAt(QPointF point, const ColorScaleStrategy &colorScaleStrategy, QSize viewportSize) const;

  QRectF getRect(QSize viewportSize) const;

private:
  /** Paint color scale */
  void paintColorScale(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext);
  /** Paint labels */
  void paintLabels(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext);
};

#endif