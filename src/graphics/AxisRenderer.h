#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"

enum Axis
{
  X,
  Y,
  Z
};

class AxisRenderer : public Renderer<Axis>
{
public:
  AxisRenderer();

  void render(const Axis &axis, const ViewController &viewController) override;

private:
  void loadShader();
  void loadBuffers();

  QOpenGLShaderProgram shaderProgram;
  QOpenGLVertexArrayObject vertexArray;
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};
  uint indexCount;
};

#endif