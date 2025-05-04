#ifndef VELOCITY_RENDERER_H
#define VELOCITY_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"
#include "shapes/ArrowFactory.h"
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

  void render(const Particle &particle, const AppContext &appContext) override;

private:
  void loadShader();
  void loadBuffers();

  QMatrix4x4 getBodyModelMatrix(QVector3D center, QVector3D direction, float width, float height) const;
  QMatrix4x4 getHeadModelMatrix(QVector3D center, QVector3D direction, float width, float height) const;

  QOpenGLShaderProgram shaderProgram;
  QOpenGLVertexArrayObject vertexArray;
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};

  struct IndexBuffers
  {
    QOpenGLBuffer arrowHead{QOpenGLBuffer::IndexBuffer};
    QOpenGLBuffer arrowBody{QOpenGLBuffer::IndexBuffer};
  } indexBuffers;

  ArrowFactory arrowFactory{24};
};

#endif