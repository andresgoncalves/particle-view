#ifndef AXES_RENDERER_H
#define AXES_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"

/** Render rotated axes */
class AxesRenderer : public Renderer<void>
{
public:
  /** Create axes renderer */
  AxesRenderer();

  /** Render axes in viewport */
  void render(const AppContext &appContext) override;
  /** Render axes in viewport */
  void render(const AppContext &appContext, QPainter &painter, QSize viewportSize) override;

private:
  /** Load shaders */
  void loadShader();
  /** Load buffers */
  void loadBuffers();

  /** Axis labels */
  const char *axisLabels[3] = {"x", "y", "z"};
  /** Axis colors */
  QColor axisColors[3] = {
      QColor::fromRgbF(1.0f, 0.0f, 0.0f),
      QColor::fromRgbF(0.0f, 1.0f, 0.0f),
      QColor::fromRgbF(0.0f, 0.0f, 1.0f),
  };
  /** Axis rotations */
  QMatrix4x4 modelMatrices[3] = {
      QMatrix4x4{},
      QMatrix4x4{},
      QMatrix4x4{},
  };

  /** Paint axes */
  void paintAxes(QMatrix4x4 modelViewProjectionMatrices[3], const AppContext &appContext, QPainter &painter, QSize viewportSize);
  /** Paint labels */
  void paintLabels(QMatrix4x4 modelViewProjectionMatrices[3], const AppContext &appContext, QPainter &painter, QSize viewportSize);

  /** Renderer shader */
  QOpenGLShaderProgram shaderProgram;
  /** Shape vertex array object */
  QOpenGLVertexArrayObject vertexArray;
  /** Shape vertex buffer */
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
  /** Shape index buffer */
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};
  /** Shape index count */
  int indexCount;
};

#endif