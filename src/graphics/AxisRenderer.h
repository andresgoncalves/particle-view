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

  void render(const Axis &axis, const RenderController &renderController) override;

private:
  void loadShader();
  void loadBuffers();
  void loadVertices(std::vector<float> &vertices, size_t divisions = 24);
  void loadIndices(std::vector<uint> &indices, size_t divisions = 24);

  QOpenGLShaderProgram shaderProgram;
  QOpenGLVertexArrayObject vertexArray;
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};
  uint indexCount;
};

#endif