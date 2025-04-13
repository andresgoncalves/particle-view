#ifndef VELOCITY_RENDERER_H
#define VELOCITY_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"
#include "../models/Particle.h"

enum Axis
{
  X,
  Y,
  Z
};

class VelocityRenderer : public Renderer<Particle>
{
public:
  VelocityRenderer();

  void render(const Particle &particle, const ViewController &viewController) override;

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