#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"
#include "../models/Particle.h"

class ParticleRenderer : public Renderer<Particle>
{
public:
  ParticleRenderer();

  void render(const Particle &particle, const AppContext &appContext) override;

private:
  void loadShader();
  void loadBuffers();

  bool shouldRender(const Particle &particle, const AppContext &appContext);
  void drawElements(ViewController::ParticleShape mode);

  QOpenGLShaderProgram shaderProgram;
  QOpenGLVertexArrayObject vertexArray;
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};

  struct IndexBuffers
  {
    QOpenGLBuffer solid{QOpenGLBuffer::IndexBuffer};
    QOpenGLBuffer skeleton{QOpenGLBuffer::IndexBuffer};
  } indexBuffers;
};

#endif