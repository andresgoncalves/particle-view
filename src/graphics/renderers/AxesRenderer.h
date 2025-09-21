#ifndef AXES_RENDERER_H
#define AXES_RENDERER_H

#include <array>

#include <QtGui/QColor>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLFunctions>

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <graphics/RenderContext.h>

#include "Renderer.h"

/** Axes renderer */
class AxesRenderer : protected Renderer
{
public:
  /** Create axes renderer */
  AxesRenderer();

  /** Render axes */
  void render(RenderContext &renderContext);

private:
  /** Initialize buffers */
  void initBuffers();

  /** Get rotated matrices */
  std::array<QMatrix4x4, 3> getMatrices(RenderContext &renderContext) const;

  /** Axis labels */
  std::array<const char *, 3> axisLabels = {"x", "y", "z"};
  /** Axis colors */
  std::array<QColor, 3> axisColors = {
      QColor::fromRgbF(1.0f, 0.0f, 0.0f),
      QColor::fromRgbF(0.0f, 1.0f, 0.0f),
      QColor::fromRgbF(0.0f, 0.0f, 1.0f),
  };

  /** Shape vertex array object */
  QOpenGLVertexArrayObject vertexArray;
  /** Shape vertex buffer */
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
  /** Shape index buffer */
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};
};

#endif