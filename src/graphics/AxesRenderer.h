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

private:
  /** Load shaders */
  void loadShader();
  /** Load buffers */
  void loadBuffers();

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